#include <iostream>
#include <mutex>
#include <thread>
#include <string>
#include <vector>
#include <chrono>
#include <fstream>
#include <algorithm>

// int main() {
//     std::string str;
//     std::thread t{[&str](){
//         str = "Hello";
//         std::this_thread::get_id();
//     }};
//     t.join();
//     return 0;
// }

// add_compile_options(-fsanitize=thread)
// add_link_options(-fsanitize=thread)

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

    threads.emplace_back(std::thread{[&vec, middle]{
        std::sort(vec.begin(), middle);
    }});
    threads.push_back(std::thread{[&vec, middle]{
        std::sort(middle, vec.end());
    }});


    std::vector<int> result(vec.size());
    std::merge(vec.begin(), middle, middle, vec.end(), result.begin());

    for (std::thread& thread : threads) {
        thread.join();
    }

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);



}