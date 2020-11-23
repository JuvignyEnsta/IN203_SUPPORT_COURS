#include <thread>
#include <iostream>

void incremente_counter(int& counter)
{
    for (int i = 0; i < 5; ++i )
    {
        counter = counter + 1;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
void divide_by_two_if_even(int& counter)
{
    for (int i = 0; i < 5; ++i )
    {
        if (counter %2 == 0) counter /= 2;
        else counter = counter + 1;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main()
{
    int counter = 0;
    std::thread t1(incremente_counter, std::ref(counter));
    std::thread t2(divide_by_two_if_even, std::ref(counter));

    t1.join();
    t2.join();
    std::cout << "compteur final : " << counter << std::flush << std::endl;
    return EXIT_SUCCESS;    
}