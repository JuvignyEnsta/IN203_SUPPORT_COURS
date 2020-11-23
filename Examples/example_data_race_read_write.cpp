#include <thread>
#include <iostream>


void increment_counter(int& counter)
{
    for ( int i = 0; i < 11; ++i )
    {
        ++ counter;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void display_counter(const int& counter)
{
    for (int i = 0; i < 10; ++i )
    {
        std::cout << counter << " " << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));        
    }
}

int main()
{
    int counter = 0;
    std::thread t1(increment_counter, std::ref(counter));
    std::thread t2(display_counter, std::cref(counter));
    t2.detach();

    t1.join();
    return EXIT_SUCCESS;
}