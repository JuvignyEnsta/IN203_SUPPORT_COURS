#include <thread>
#include <atomic>
#include <iostream>

std::atomic<int> value1, value2;

void increment_value1_and_decrement_value2() {
    std::cout << "Start increment value 1 decrement value 2" << std::flush << std::endl;
    for ( int i = 0; i < 100; ++i ) {
        value1 ++; value2 --;
    }
    std::cout << "End increment value 1 decrement value 2" << std::flush << std::endl;
}

void increment_value2() {
    std::cout << "Start increment value 2" << std::flush << std::endl;
    for ( int i = 0; i < 50; ++i ) {
        value2 ++;
    }
    std::cout << "End increment value 2" << std::flush << std::endl;
}

void increment_both_values() {
    std::cout << "Start increment values 1 and 2" << std::flush << std::endl;
    for ( int i = 0; i < 100; ++i ) {
        value1 ++; value2 ++;
    }
    std::cout << "End increment values 1 and 2" << std::flush << std::endl;
}

int main() {
    std::thread t1(increment_value1_and_decrement_value2);
    std::thread t2(increment_value2);
    std::thread t3(increment_both_values);

    t1.join(); t2.join(); t3.join();
    std::cout << "value 1 vaut au final : " << value1 << " et value2 vaut : " << value2 << std::flush << std::endl;
    return EXIT_SUCCESS;
}
