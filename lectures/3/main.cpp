#include <iostream>
#include <string>
#include <mutex>

class ListNode {
public:
    explicit ListNode(size_t size, int data)
        : size_(size), data_(data) {
    }

    size_t get_size() const {
        return size_;
    }

    explicit operator int() const {
        return data_;
    }

private:
    size_t size_;
    ListNode* head_;
    int data_;
};

void print_size(const ListNode& list) {
    std::cout << "list size is: " << list.get_size() << std::endl;
}



class ListNode1 {
public:
    explicit ListNode1(int data)
        : data_(data), head_(nullptr) {
    }

    ListNode1(const ListNode1& other) {
        size_ = other.size_;
        data_ = other.data_;
        if (other.head_) {
            head_ = new ListNode1(other.head_->data_);
        }
    }

    // ListNode1 operator=(const ListNode1 other) {
        
    // } // should be there

    void add(int data) {
        if (head_) {
            delete head_;
        }
        head_ = new ListNode1(data);
        ++size_;
    } 

    size_t get_size() const {
        return size_;
    }

    explicit operator int() const {
        return data_;
    }

    ~ListNode1() {
        delete head_;
    }

private:
    int data_;
    size_t size_;
    ListNode1* head_;
};

// RAII
struct File {
    File(const std::string& str) {
        file_=::fopen(str.c_str(), "w"); // оператор разрешения области видимости: в данном случае обращаемся в глобальному пространству имен файла
        // m.lock();
    }
    ~File() { // можем управлять множеством ресурсов в рамках 1-ого класса, причем класс - единоличный владелец РЕСУРСОВ
        std::cout << "closed" << std::endl;
        ::fclose(file_); // при выходе из каой-либо области видимости файл закроется
        // m.unlock();
    }
private:
    FILE* file_;
    // static std::mutex mu;
};

struct Registered {
public:
    static Registered CreateRegistered() {
        return Registered();
    }
private:
    Registered() {}; // запрет на создание
};



// наследование

class Person {
public:
    void SetName(const std::string name) {
        name_ = name;
    }
    std::string GetName() const {
        return name_;
    }

private:
    std::string name_;
    std::string surname_;
};

class Worker : public Person {
    void SetDuty(const std::string& duty) {
        duty_ = duty;
    }
private:
    std::string duty_;
};

void print_info(const Person& person) {
    std::cout << person.GetName();
}


//------------

struct InnerData {
    InnerData() {
        std::cout << "inner data created" << std::endl;
    }
    ~InnerData() {
        std::cout << "innerdata destroyed" << std::endl;
    }
};

struct Base {
    Base() {
        std::cout << "base created" << std::endl;
    }
    virtual int get_int() {
        return 2;
    }
    virtual ~Base() {}; // с virtual компилятор найдет именно компилятор Child в таблице virtual методов и вызовет его
};

struct Child: public Base {
    Child() {
        std::cout << "child created" << std::endl;
    }
    InnerData data_;
};

struct Child2: public Base {
    Child2() {
        std::cout << "child2 created" << std::endl;
    }
    InnerData data_;
};

// protected: деструктор можно сделать приватным, тогда нельзя будет явно вне Base и наследников удалить объект через delete
//     ~Base() {};


// АБСТРАКТНЫЕ КЛАССЫ
struct BaseFile {
    virtual ~BaseFile() {};
    virtual std::string read_line() = 0;
};

struct TextFile : public BaseFile {
    std::string read_line() override {};
};

struct ZipFile : public BaseFile {
    std::string read_line() override {};
};

void CountFilms(const BaseFile& file) {}; // логика работы никак не меняется, меняются внутренние алгоритмы работы с данными


//--- абстрактные классы

struct Color {
    int r, g, b;
};

struct ImgProvider {
    virtual Color getBackgroundColor() = 0;
};

struct MyImgProvider : public ImgProvider {
    Color getBackgroundColor() override {
        return {0, 0, 0};
    }
};

void CreateImg(const ImgProvider& img) {
    std::cout << "creating img" << std::endl;
}

int main() {
    ListNode l(10, 20);
    //print_size(ListNode(10)); // конвертирующие конструкторы(конструктор вызывается неявно) - выведет 10
    //print_size(true); // эквивалентно print_size(ListNode{true}) выведет 1
    // поэтому лучше использовать явное преобразование: excplicit не позволит сделать неявное преобразование параметров

    //int data = l; // неявное преобразование за счет перегрузки оператора int(), лучше его тоже помечать explicit
    // тогда будет работать только явное преобразование типов:
    int data = static_cast<int>(l); // OK

    // сейчас даже конструкторы с несколькими параметрами - конвертирующие (лучше помечать через explicit)
    // print_size({10, 20}) -- should be explicit

    //---------
    // в идеале следуем правилу 0: без своих реализаций специальных методов
    // если сделали хотя бы одну из реализаций конструкторов/деструктор - компилятор не сможет предоставить реализации по умолчанию
    // потому следуем правилу 5: объявляем все нужные методы

    ListNode1 l1(10);
    l1.add(2);

    Registered::CreateRegistered();

    Worker w;

    // print_info(w); также будет работать с наследниками: работает только через ссылки/указатели
    // неявное преобразование

    //*mutable - дает возможность изменения данных класса даже в const методах 

    Child* ch = new Child();

    Base* b = ch;

    delete b; // если базовый класс будет иметь virtual методы -- то здесь вызовется именно деструктор Base(если его деструктор не является virtual) -- InnerData не будет удален -- утечка 
    // деструктор должен быть виртуальным

    // если ПРЕДПОЛАГАЕТСЯ НАСЛЕДОВАНИЕ -- ПУБЛИЧНЫЙ ДЕСТРУКТОР ДОЛЖЕН БЫТЬ ВИРУТАЛЬНЫМ


    // ПРИВЕДЕНИЕ ТИПОВ

    // ПРОВЕРКИ std::numeric_limits перед кастом

    //DOWNCAST БАЗОВОГО КЛАССА В НАСЛЕДНИКА

    Child child;
    Child2 child2;

    Base& base_ref = child;
    

    Child2& child_ref = static_cast<Child2&>(base_ref); // DOWNCAST -- UB

    
    // через static_cast любые преоразования с void*

    Child2& child_ref_ = dynamic_cast<Child2&>(base_ref); // безопасный DOWNCAST

}