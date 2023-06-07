#include <map>
#include <fcntl.h>
#include <string>
#include <iostream>

enum Error {
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
        Error init(const std::string& name) {
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

class Base {};

class Child : public Base {
    public:
        Child() { // лучше не выделять руками память в constructor initializer list
            buf = new Base;
            try {
                foo();
            }
            catch (...) {
                delete buf;
            }
        }
    private:
        Base* buf;
};

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
