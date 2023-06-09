#include <iostream>
#include <algorithm>
#include <memory>
#include <string>
#include <vector>
#include <array>
#include <type_traits>
#include <unordered_map>
#include <sstream>
#include <iomanip>
#include <chrono>

//#include <stdexcept>

struct Containable {

    //virtual Containable& get_data() const = 0;
    virtual ~Containable() = default;
};

struct Integer : public Containable {
public:
    Integer(int i): i_(i) {};

    int get_data() const {
        return i_;
    }

private:
    int i_;
};

struct String : public Containable {
public:
    String(const std::string& str): data(str) {}

    std::string get_data() const {
        return data;
    }

private:
    std::string data;
};

class Vector {
public:
    Vector(): data_(nullptr), size(0), capacity(0) {}

    void add(Containable* i) {
        if (size == capacity) {
            size_t new_capacity = std::max(size * 2, 1ul);
            void* result = ::realloc(data_, new_capacity * sizeof(Containable*));
            if (!result) {
                throw std::bad_alloc();
            }
            data_ = static_cast<Containable**>(result);
            capacity = new_capacity;
        }
        data_[size++] = i;
    }

    void add_(Containable* i) {
        if (size == capacity) {
            size_t new_capacity = std::max(size * 2, 1ul);
            Containable** result = static_cast<Containable**>(new Containable*[new_capacity]);
            if (!result) {
                throw std::bad_alloc();
            }
            delete[] data_;
            data_ = result;
            capacity = new_capacity;
        }
        data_[size++] = i;
    }

    Containable* operator[](size_t i) const {
        return data_[i];
    }
 
    ~Vector() {
        for (size_t i = 0; i != size; ++i) {
            delete data_[i];
        }
        delete[] data_; // ok with free(data_)
    }// also works fine with add_ reallization, i.e. new[] - delete[] matching insted of realloc

    // Containable*& operator[](size_t i) {
    //     return data_[i];
    // }

private:
    Containable** data_; // массив полиморфных потомков Containable
    size_t size;
    size_t capacity;
};


template <typename A, typename B, typename C>
class Tuple {
    A a;
    B b;
    C c;
};

template <class T> // typename == class 
void func(const T& data) {}




template <typename T>
using VectorIt = std::vector<T>::iterator;
// VectorIt<int> iterator = vec.begin();

// более длинный аналог из старого стандарта
template <typename T>
struct VectorIt_ {
    typedef typename std::vector<T>::iterator type;
};
// обращение: VectorIt<int>::type iterator = vec.begin();


template <int i> // параметр шаблона "не тип"
void print() {
    std::cout << i << std::endl;
}

template <std::ostream& i>
void print_() {
    i << "123" << std::endl;
}

template <size_t rows,size_t cols>
class Matrix {
public:
    int& set(size_t i, size_t j) {
        return data[i][j];
    }
private:
    using InnerData = std::array<int, cols>;
    std::array<InnerData, rows> data;
};


bool isEqual(int a, int b) {
    return a == b;
}

bool isEqual(float a, float b) {
    return std::abs(a - b) < 1e-6; // разная точность в зависимости от регистра, в котором хранится число
} // алгоритм отличается в зависимости от типа

template <typename T>
bool isEqual(T a, T b) {
    return a == b;
}

// специализация шаблона для типа double(происходит на этапе компиляции)
template <> // можем сами указывать явно
bool isEqual<double>(double a, double b) {
   return std::abs(a - b) < 1e-6;
}// полная специализация

template <typename T>
inline bool IS_FLOATING_POINT = false;

template<> // полная специализация
inline constexpr bool IS_FLOATING_POINT<float> = true;

template<>
inline constexpr bool IS_FLOATING_POINT<double> = true;

template<>
inline constexpr bool IS_FLOATING_POINT<long double> = true;

template <typename T>
inline constexpr bool IS_CONST = false;

template <typename T> // частичная специализация
inline constexpr bool IS_CONST<const T> = true;

struct Name {
    std::string first_name;
    std::string last_name;

    bool operator==(const Name& other) const {
        return first_name == other.first_name && last_name == other.last_name;
    }

};

// вместо написания своего хеша и подстановки его в специализацию можем конкретизировать стандартный std::hash
template<>
struct std::hash<Name> {
    int operator()(const Name& name) const {
        return std::hash<std::string>{}(name.first_name + name.last_name);
    }
};


template <typename T, size_t N>
struct VectorCreator {
    static std::vector<T> create_vector() {
        std::vector<T> v;
        v.resize(N);
        return v;
    }
};

template <typename T>
struct VectorCreator<T, 10> {
    static std::vector<T> create_vector() {
        std::cout << "partial spec for size 10";
        std::vector<T> v;
        v.resize(10);
        return v;
    }
};


struct CoutSink {
    static auto& get() {
        return std::cout;
    }
};

struct CerrSink {
    static auto& get() {
        return std::cerr;
    }
};

struct DefaultFormatter {
    static const std::string& format(const std::string& data) {
        return data;
    }
};

struct TimeFormatter {
    static std::string format(const std::string& data) {
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&t), "%T") << " ";
        ss << data;
        return ss.str();
    }
};

template <typename Sink, typename Formatter=DefaultFormatter> // пример статического полиморфизма
class Log {
public:
    void log(const std::string& data) {
        Sink::get() << Formatter::format(data) << std::endl;
    }
};



int main() {
    Vector v;

    //Integer a = 10; no suitable conversion
    //v.add(a);

    v.add_(new Integer{10});
    // v.add_(new String{"hey"});

    std::cout << dynamic_cast<Integer*>(v[0])->get_data() << std::endl;
    //std::cout << dynamic_cast<String*>(v[1])->get_data() << std::endl;

    // такой подход применим, но:
    // 1 - постоянно делаем касты, в которых легко ошибиться, то сеть нет ограничений и согласований типа на уровне языка
    // 2 - касты требуют ресурсов

    std::vector<int> vv{1, 2, 3};
    VectorIt<int> it = vv.begin();

    std::array<int, 5> arr; // шаблоны "тип" + "не тип"

    Matrix<2, 5> matrix; 
    Matrix<5, 2> matrix1; // абсолютно разные типы при компиляции

    //в основном используется для строгой статической типизации по размерности, где это нужно (матрчиные операции и тп)

    // std::cout << std::is_same_v<decltype(matrix), decltype(matrix1)> << std::endl; // 0

    bool t1 = isEqual<double>(0.22, 0.699999999999); // специализация шаблона

    std::cout << IS_FLOATING_POINT<int> << std::endl;
    std::cout << std::is_floating_point<int>::value << std::endl;

    // для работы с битами - std::bitset

    // примеры частичной специализации:
    // std::vector<int>
    // т.к. полная специализация предполагает также конкретизацию аллокатора

    char j = 0b001011101;
    bool h = (j >> 2) & 0x01;
    std::cout << h << std::endl; // 1

    std::unordered_map<Name, int> map;

    map[Name{"Vasya", "Ivanov"}] = 10;

    Name name {"Vasya", "iVANOV"};
    map[name] = 11;

    std::cout << map[Name{"Vasya", "Ivanov"}] << std::endl; // 10
    std::cout << map[name] << std::endl; // реализации const operator==(т.к. вставляем rvalue, для него допустим только const lvalue ref) достаточно для работы с не const объектами

    Log<CoutSink, TimeFormatter> logger;
    logger.log("hello");

}
// Если функция шаблонная (template) или инлайновая (inline), то без вариантов следует размещать и объявление, 
// и реализацию в заголовочном файле, потому что шаблонные функции по сути текстовые шаблоны, и их компилятор не сможет "извлечь" из CPP.

// Если объявление и определение инлайновой функции не разместить в заголовочном файле, 
// то на стадии сборки посыпятся ошибки, что "определение функции не найдено".