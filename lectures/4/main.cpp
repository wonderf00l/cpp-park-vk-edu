#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <unistd.h>
#include <fcntl.h>
#include <memory>

std::ifstream get_file() { 
    std::ifstream f;
    f.open("123.txt");
    return f;
}


struct File {
    File(const std::string& name){
        fd_ = ::fopen(name.c_str(), "r");
    }

    File(const File& other) = delete;
    File& operator=(const File& other) = delete;

    ~File() {
        ::fclose(fd_);
    }

private:
    //int fd_;
    FILE* fd_;
};

// частичное решение проблемы(однако RAII больше нет)

// must delete
std::ifstream* get_file_() { 
    std::ifstream* f = new std::ifstream();
    f->open("123.txt");
    return f;
}



// указатели при полиморфизме

struct BaseFile {
    virtual void read() = 0;
    virtual ~BaseFile();
};

struct TxtFile : public BaseFile {};

struct GzFile : public BaseFile {};

// BaseFile* get_file__() {
//     BaseFile* f = new Txtfile();
//     // f.open("123.txt");
//     //check filetype -- some logic
//     return f;
// }

std::vector<int> Data(int i) {
    std::vector<int> v;
    v.push_back(i);
    return v; // лишнее копирование временного объекта
}


// move - семантика

struct File_ {
    File_(const std::string& name){
        fd_ = ::open(name.c_str(), O_RDONLY);
    }

    File_(File_& other) {
        fd_ = other.fd_;
        other.fd_ = -1;

        // fd_ = std::exchange(other.fd_, -1);
    }

    File_(File&& other);
    File_& operator=(File&& other);

    File_& operator=(File_& other){
        if (fd_ > 0){
            close(fd_);
        }
        fd_ = other.fd_;
        other.fd_ = -1;
        return *this;
    }

    ~File_() {
        if (fd_ > 0) {
            ::close(fd_);
        }
    }

private:
    int fd_;
};

void foo(const std::string& val) {}
void boo(std::string&& val) {};

void is_rvalue(std::string&& s) { // по таким ссылкам передаем объекты, которые будут уничтожены на выходе из области видимости/в ближайшее время
    std::cout << "is_rval" << std::endl;
}

void is_rvalue(const std::string& s) {
    std::cout << "is_lval" << std::endl;
}

// modern C++

std::ifstream get_file___() {
    return std::ifstream("123.txt", std::ifstream::in);
}

void pass_file(std::ifstream&& file) {}

void pass_f_without_move_sem(std::ifstream& file) { // однако такая сигнатура неявна: непонятно, это частичное изменение или захват всех ресурсов
    std::ifstream f;
    f.swap(file); // результат аналогичен использованию std::move и rval ссылок
}

struct Node; // forward declaration
using NodePtr = std::unique_ptr<Node>;

struct Node {
    int data;
    NodePtr next;

    explicit Node(int i): data(i) {}
};

class List {
public:
    List(): head(NodePtr(nullptr)) {}

    void add(int i) {
        if (!head) {
            head.reset(new Node(i));
            // (NodePtr) tail = std::move(head); - bye, head -- not correct -- только один указатель владеет ресурсом полностью(включая удаление), другой указатель должен быть сырым
            tail = head.get();
            return;
        }

        // Node* tail = head.get();  если нет tail
        // while (tail->next) {
        //     tail = tail->next.get();
        // }
        // tail->next.reset(new Node(i));

        tail->next.reset(new Node(i));
        tail = tail->next.get();

    }
    // ~List(); при выходе из scope вызывается деструктор дефолтный деструктор List, он начнет уничтожать члены данных, вызовется деструктор head, он уничтожает Node, у ноды вызывается свой деструктор, ..., и так до tail включительно
private:
    NodePtr head;
    Node* tail;
};

void print(std::shared_ptr<std::string> str_ptr) {
    std::cout << "use count inside func: " << str_ptr.use_count() << std::endl;
    std::cout << "value on sptr: " <<  *str_ptr << std::endl;
}


struct Node_; // forward declaration
using NodeSPtr = std::shared_ptr<Node_>;

struct Node_ {
    int data;
    NodeSPtr next;

    explicit Node_(int i): data(i) {}
};

class List_ {
public:
    List_(): head(NodeSPtr(nullptr)) {}

    void add(int i) {
        if (!head) {
            head.reset(new Node_(i));
            tail = head;
            return;
        }

        tail->next.reset(new Node_(i));
        tail = tail->next;

    }
    // ~List(); при выходе из scope вызывается деструктор дефолтный деструктор List, он начнет уничтожать члены данных, вызовется деструктор head, он уничтожает Node, у ноды вызывается свой деструктор, ..., и так до tail включительно
private:
    NodeSPtr head;
    NodeSPtr tail;
};


struct Node__; // forward declaration
using NodeSPtr_ = std::shared_ptr<Node__>;

struct Node__ {
    int data;
    NodeSPtr_ next;
    std::weak_ptr<Node__> prev; // если NodeSptr_ prev, то утечка

    explicit Node__(int i): data(i) {}
};

class List__ {
public:
    List__(): head(NodeSPtr_(nullptr)), tail(NodeSPtr_(nullptr)) {}

    void add(int i) {
        if (!head) {
            head.reset(new Node__(i));
            tail = head;
            return;
        }

        tail->next.reset(new Node__(i));
        tail->next->prev= tail;
        tail = tail->next;

    }
private:
    NodeSPtr_ head;
    NodeSPtr_ tail;
};


int main() {
    std::ifstream f = get_file(); // конструктор копирования ifstream запрещен
                                  // т.к. при копировании копируется дескриптор файла, то есть есть риск закрыть один файл 2 раза

    // BaseFile* ff = get_file__(); // полиморфизм только через указатели

    foo(std::string("striing")); // OK
    const std::string& ref = std::string("123"); // OK

    std::string&& ref_ = std::string("123");

    std::string st = std::string("213");

    is_rvalue(std::string("123")); // rval
    is_rvalue(st); // lval
    is_rvalue(ref); // lval (type: rval on int)
    // is_rvalue(moo());

    // auto&& s = 10; && not always rval

    std::ifstream ff = get_file___();

    // std::ifstream&& rval = f; an rvalue reference cannot be bound to an lvalue

    // std::ifstream&& rval = static_cast<std::ifstream&&>(f); //OK

    std::ifstream src_dest = std::move(ff); // тот же static_cast к rvalue + преобразование типов для правильного каста
    // при вызове std::move делается явный каст к типу rvalue -- т.к. создается новый объект через rvalue объект, вызывается конструктор перемещения
    std::cout << ff.is_open() << std::endl; // 0 -- через std::move(ff) обозначили, что это rval, т.е. ресурсы можно отобрать -- отбираем, кладем заглушку
    std::cout << src_dest.is_open() << std::endl; // 1

    std::ifstream&& rval_ref = std::move(src_dest);
    std::cout << src_dest.is_open() << std::endl; // 1 -- не забирали ресурсы у объекта
    std::cout << rval_ref.is_open() << std::endl; // 1 -- просто создали rval ссылку на него, для этого понадобился std::move для явно каста в rvalue

    // pass_file(src_dest); an rvalue reference cannot be bound to an lvalue
    pass_file(std::move(src_dest)); // все манипуляции непосредственно по перемещению и захвату ресурсов происходят в конструкторах/операторах перемещения объектов

    // УМНЫЕ УКАЗАТЕЛИ

    std::unique_ptr<std::vector<int>> u_ptr(new std::vector<int>({1, 2, 3}));

    std::vector<int>* ptr = u_ptr.get();
    std::cout << u_ptr.get()->size() << std::endl;
    std::cout << u_ptr->size() << std::endl; // same

    std::vector<int>& s_ref = *(u_ptr.get());
    std::vector<int>& ss_ref = *u_ptr;

    std::string str;
    // std::unique_ptr<std::string> ptr(&str); dobule free: сначала деструктор unique_ptr удалить ресурсы по адресу, затем деструктор std::string сделает то же самое


    auto str_sptr = std::make_shared<std::string>("234");
    auto str_uptr = std::make_unique<std::string>("567"); 
    std::cout << str_sptr.use_count() << std::endl; // 1
    print(std::make_unique<std::string>("123")); //OK: передаем rvalue, видимо, неявное преобразование uptr в sptr; // use_count == 1
    print(str_sptr); // use_count == 2
    std::cout << str_sptr.use_count() << std::endl; // 1

    // print(str_uptr); не работает для uptr: единоличное владение, либо применять std::move, но это не то что нужно

    List_ l;
    l.add(10);
    l.add(20);
    l.add(30);

}                                 

