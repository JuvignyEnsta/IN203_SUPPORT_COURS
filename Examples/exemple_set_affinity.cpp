#include <thread>
#include <iostream>
#include <string>
#include "thread_extension.h"

void affiche_mon_gpu(const std::string& name)
{
    for ( int i = 0; i < 100; ++i )
    {
        std::cout << name << " sur le processeur logique " << thread::get_cpu() << std::flush << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main()
{
    std::thread t1(affiche_mon_gpu, "Premier thread");
    thread::set_affinity(t1.native_handle(), 1<<0);
    std::thread t2(affiche_mon_gpu, "Deuxieme thread");
    thread::set_affinity(t2.native_handle(), 1<<2);
    std::thread t3(affiche_mon_gpu, "Troisieme thread");
    thread::set_affinity(t3.native_handle(), 1<<4);

    t1.join();
    t2.join();
    t3.join();

    return EXIT_SUCCESS;
}