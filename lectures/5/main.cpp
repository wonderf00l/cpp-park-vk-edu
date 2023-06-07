#include <map>
#include <fcntl.h> // open
#include <string>
#include <iostream>
#include <memory>
#include <unistd.h> // close
#include <list>
#include <fstream>


enum Error_ {
    OK = 0,
    FILE_OPEN_ERROR = 1
};

void parse_line(const std::string& str) { // неочевидное, недопустимое поведение
    if (str.size() < 50) {
        std::cout << "bad str" << std::endl;
        exit(0);
    }
    // logic
}

class File { // подход для отдачи кода возврата при рабоет с C++ классами
    public:
    File() {};
        Error_ init(const std::string& name) {
            fd = ::open(name.c_str(), std::ios::out);
            if (fd < 0) {
                return FILE_OPEN_ERROR;
            }
            return OK;
        }
    private:
        int fd;
};

void print_smth(const std::string& str) {
    if (str.size() < 50) {
        throw std::invalid_argument("short string");
    }
    throw std::exception(); // can throw anything: int, str, std::runtime_error etc
}


// принято писать собственную иерархию классов-иссключений, для обработки ошибок логики собственных функций
// и заносить это в отдельный файл

struct Error : public std::runtime_error {
    using std::runtime_error::runtime_error; // заносим namespace runtime_error(класс runtime_error) внутрь класса для создания кастомного исключения, поведение которого идентично runtime_error
    // такое исключение может принимать сообщение как аргмент конструктора
};

struct LongArg : public Error {
    using Error::Error;
};

void foo();

class Base {
    public:
        ~Base() {
            throw; // при вызове деструктора Child вызовется деструктор Base -- throw -- деструктор Child не отработает корректно -- деструктор uptr не будет вызван -- утечка (сценарий, есил одно из полей Child - Base base_obj_attr, а не Base*)
        }
};

class Child : public Base {
    public:
        Child() { // лучше не выделять руками память в constructor initializer list
            buf = new Base; // with upt: buffer_.reset(new Base); or : buffer_{new Base} - in init list
            try {
                foo();
            }
            catch (...) {
                delete buf;
            }
        }
    private:
        Base* buf; // лучше: std::unique_ptr<Base> buffer_;
        std::unique_ptr<int> data_;
};

// В ДЕСТРУКТОРЕ НЕ КИДАЮТСЯ ИСКЛЮЧЕНИЯ, Т.К. В ТАКОМ СЛУЧАЕ НАРУШАЕТСЯ АЛГОРИТМ СВЕРТКИ СТЕКА И ОСВОБОЖДЕНИЯ РЕСУРСОВ

class File {
    public:
        File(const std::string& name) {
            fd_ = ::open(name.c_str(), std::ios::in);
        }

        void open(const std::string& name) {
            fd_ = ::open(name.c_str(), std::ios::in); // :: - обращаемся к глобальной области видимости
        }

        void close() {
            int res = ::close(fd_);
            fd_ = -1;
            if (res < 0) {
                throw std::runtime_error{"Error while closing file"};
            }
        }

        ~File() { // noexcept by default, можем заставить деструктор кидать исключения через noexcept(false)
            try {
                close();
            }
            catch(...) {

            } // функции, вызываемые в деструкторе, должны быть noexcept
            // либо же нужно ловить(игнорировать) исключения
            // иначе сразу вызовется std::terminate, программа упадет
        }

        // то есть noexcept функции с throw внутри инициируют вызов std::terminate, в таком случае мы не сможем перехватить его извне и продолжить работу программу с "поломанным стеком"

    private:
    int fd_;
};

void increment_integer(int& i) noexcept { // если метод гарантированно не может вызвать исклчение, помечаем noexcept, в противном случае - спорно
    ++i;
} // no exc guarantee

void func() { // при перехвате искючений в подобных функциях будет происхрдить утечка ресурсов
    int* obj = new int(10);
    throw std::runtime_error("...");
} // no exception safety


template <typename T>
class List {
    public:

        SqLiteWrapper() {};

        void add(const T& obj) {
            ++size;
            l.push_back(obj);  // если произойдет ошибка при копировании объекта, аллокации памяти, и она в итоге будет перехвачена, то список окажется в невалидном состоянии
        } // no exception safety

        // то есть нужно писать программы с расчетом на то, что при выпадании любого исключения объект останется в валидном состоянии
        // basic exception safety
    private: 
        std::list<T> l;
};


class SqLiteWrapper {
    public:

        SqLiteWrapper() {};

        SqLiteWrapper(SqLiteWrapper&& other) noexcept {} // рекомендуется помечать noexcept для оптимизации изменения разных контейнеров, если можем это гаранитровать

        void open(const std::string& name) { // отсутствует strong exception safety:
            file.open(name); // 

            if (name == "can be dangerous") {
                throw std::exception();
            }
        }

        void safe_open(const std::string& name) { // strong exception safety
            std::ofstream new_file{name};
            if (!new_file) {
                throw std::runtime_error("Got bad file");
            }

            file.close();
            file = std::move(new_file); // копирование запрещено
        }

        ofstream& get() {
            return file;
        }

    private:
        std::ofstream file;
};

// std::move - no except, т.r. присваивание простых типов не может бросить исключение
// all STL entities - strong exception safety

// инициализация полей в объявлении:
// private:
//    inline static Logger singleton_{"log.txt"}; -- допустимо

int main () {
    try {
        print_smth("str");
    }
    catch (int& i) {
        std::cout << "got " << i << " as exc";
    }
    catch (std::invalid_argument& exc) {
        std::cout << exc.what();
    }
    catch (std::exception&) {
        std::cout << "generic exceprion class";
    }
    catch (...) {
        std::cout << "got some error(catched exc or anything else)" << std::endl;
    }

    try {
        print_smth("short str");
    }
    catch(std::invalid_argument& exc) {
        std::cout << exc.what(); // залогировали - и пробросили наверх, чтобы клиент передалавал valid args
        throw;
    }

    SqLiteWrapper wrap;

    wrap.open("okay.txt");

    wrap.get() << "line 1";
    try {
        wrap.open("can be dangerous"); // здесь выкидывается исключение, при этом объект не возвращается в последнее валидное состояние
    }
    catch (...){
        std::cout << "bad file logging";
    }
                                
    wrap.get() << "line 2"; // то есть line 2 не попадет в okay.txt

    
    // correct scenario
    wrap.safe_open("okay.txt");

    wrap.get() << "line 1";

    try {
        wrap.safe_open("can be dangerous");
    }
    catch (...) {
        std::cout << "bad file logging";
    }

    wrap.get() << "line 2"; // line1 + line 2 in okay.txt
}


// ********************************
// namespaces
#include <iostream>
using namespace std;

// first name space
namespace first_space
{
void func()
{
	cout << "Inside first_space" << endl;
}
// second name space
namespace second_space
{
	void func()
	{
		cout << "Inside second_space" << endl;
	}
}
}
using namespace first_space::second_space;
int main ()
{

    // Calls function from first name space.
    first_space :: func();
	// This calls function from second name space.
	func();

	return 0;
}

// Instead of accessing the whole namespace, another option (known as using declaration) is to access a particular item within a namespace.
#include <iostream>
using std::cout;

int main ()
{
	cout << "std::endl is used with std!" << std::endl;
	return 0;
}
