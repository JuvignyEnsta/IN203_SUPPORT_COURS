#include <thread>
#include <vector>
#include <iostream>

int main()
{
    // num_cpus contiendra le nombre de processeurs logiques !
    auto num_cpus = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    threads.reserve(num_cpus);

    for ( decltype(num_cpus) i = 0; i < num_cpus; ++i )
        threads.emplace_back([](int id){std::cout << "Hello from " << id << " !" << std::endl; },i);

    std::cout << "Hello from main !" << std::endl;

    for ( auto& t : threads )
        t.join();

    return EXIT_SUCCESS;
}
