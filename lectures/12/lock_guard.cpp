#include <iostream>
#include <mutex>
#include <thread>
#include <string>
#include <vector>
#include <chrono>
#include <fstream>
#include <algorithm>


int main(int argc, char* argv[]) {
    std::vector<int> vec;

    std::ifstream  f(argv[1]);

    while(f) {
        int tmp;
        f >> tmp;
        vec.push_back(tmp);
    }

    auto start = std::chrono::steady_clock::now();

    std::vector<std::thread> threads(2);

    auto middle = std::next(vec.begin(), vec.size() / 2);

    int sum = 0;
    std::mutex mut; // лучше не делать вручную lock/unlock, а использовать RAII обертку, которая в деструкторе разлочит mutex

    // это поможет избежать дедлока, когда, например, функция выкинула исключение и послудующий код недостижим, а мьютекс остался залоченным

    threads.emplace_back(std::thread{[&mut, &sum, &vec, middle]{ // обязательна передача по ссылке в контекст лямбды
        for (auto it = vec.begin(); it != middle; ++it) {
            // mut.lock();
            std::lock_guard<std::mutex> _(mut); // при свертывании стека мьютекс разлочится
            // std::this_thread::sleep_for(std::chrono::milliseconds(10));
            sum += *it;
            // mut.unlock();
        }
    }});
    threads.push_back(std::thread{[&mut, &sum, &vec, middle]{
        for (auto it = vec.begin(); it != middle; ++it) {
            // mut.lock();
            std::lock_guard<std::mutex> _(mut);
            sum += *it;
            // mut.unlock();
        }
    }});


    {
        std::lock_guard<std::mutex> _(mut);
        // logic
    }

    for (std::thread& thread : threads) {
        thread.join();
    }

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // внутри мьютекса должно быть много полезной нагрузки - иначе поткои большую часть времени висят в локе, тогда получится приблизитсья к линейному выигрышу по времени работы

}