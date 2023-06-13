// std::vector: последвоательное расположение элементов, быстрое выполнение операций, т.к. область памяти попадает в кеш процессора
// std::deque: располагается в памяти чанками, быстрое выполнение операций, реаллокации и инвалидация адресов, как и у вектора
// std::list - двусвязный список, элементы разрежены в памяти, но нет реаллокаций --> нет инвалидации старых адресов элементов
// итераторы и адреса листа не инвалидируются + быстрое удаление из середины

// multi версии ассоциативных контейнеров позволяют хранить одинаковые ключи, они будут идти последовательно

// std::stringstream ss(str); str: id   rating   count
// ss >> Record.id >> Record.rating >> Rating.count

#include <vector>
#include <algorithm>
#include <iostream>
#include <functional>
#include <queue> 
#include <map>
#include <chrono>
#include <thread>
#include <pthread.h>

struct Data {
    int i;
};

bool comparator(const Data& lhs, const Data& rhs) {
    return lhs.i < rhs.i;
}


// LAMBDA EXPRESSIONS

// проблем с передачей функции по указателю не было еще в C
// проблема - передавать вместе с функцией какие-либо данные(например, для обработки другой фунцкией, которая ассоциирована с каким-либо потоком, чтобы, например, отличать потоки друг от друга, обраатывать разные части контейнера и тп)
// один из вариантов - прокидывать сущность(фунцию, функтор) через void*, либо через шаблон
// передавать функтор (класс/структуру с оператором вызова и теми самыми данными в pivate-секции)

struct MyTask {

    MyTask(int data): data(data) {}

    void operator()() {
        std::cout << data << std::endl;
    }
    private:
        int data;
};

template <typename T>
void processor(T entity) {
    entity();
}

using Task = std::function<void()>;
// void(*func)() --> void() - тип: функция, которая ничего не принимает и ничего не возвращает
// std::function принимает любой функциональный объект(лямбда, функтор, глобальная фунцкция, метод)

struct Scheduler{
public:
    void Add(Task task) {
        tasks.push(task);
    }
    void Run() {
        while (!tasks.empty()) {
            Task t = std::move(tasks.front());
            tasks.pop();
            t();
        }
    }
private:
    std::queue<Task> tasks; // благодаря std::function можем хранить в контейнере разные функции(разные функциональные типы данных)
};

// вместо того, чтобы писать много кода по созданию функтора с private-секцией захвта, как аналог можно использовать лямбды, это то же самое
// лямбду можно передавать в функцию, возвращать из функции, создавать как переменную

// лямбда позволяет отвязать передаваемые в функцию данные от аргументов функции и положить их в область захвата, тогда она может не принимать параметров

int main() {
    std::vector<int> v{5, 4, 2, 10, 0};

    std::sort(v.begin(), v.end(), &comparator); // &func - передаем указатель на функцию

    processor<MyTask>(MyTask{10});

    int data = 10;

    processor([&data](){ // здесь шаблон - labmda функция, по сути, класс-функтор __labmda_x_y, который уникален для каждой лямбды
        std::cout << data << std::endl;
    }); // &entity - передача сущности по ссылке в область захвата, default - копия по значению

    // у каждой лямбды уникальный тип, поэтому их можно объявить только через auto

    auto l1 = [](){};
    auto l2 = [](){};
    // l1 = l2 - ERROR, different types
    auto l3 = l1; // OK

    Scheduler scheduler;
    scheduler.Add([](){
        std::cout << "1" << std::endl;
    });
    auto delayer = [](){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    };
    scheduler.Add([&delayer](){
        std::cout << "2" << std::endl;
        delayer();
    });

    auto bb = [n = int(10)]() {
        std::cout << n << std::endl; // можно объявлять локлаьные перемнные в обалсти захвата
    }

}