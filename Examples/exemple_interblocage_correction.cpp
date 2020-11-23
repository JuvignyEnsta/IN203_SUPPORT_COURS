#include <thread>
#include <mutex>
#include <iostream>

std::mutex lock_value1;
std::mutex lock_value2;

int value1, value2;

void increment_value1_and_decrement_value2() {
    std::cout << "Start increment value 1 decrement value 2" << std::flush << std::endl;
    for ( int i = 0; i < 100; ++i ) {
        std::lock(lock_value1, lock_value2);
        value1 ++; value2 --;
        std::cout << "++value 1 : " << value1 << ", --value 2 : " << value2 << std::flush << std::endl;
        lock_value1.unlock();
        lock_value2.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    std::cout << "End increment value 1 decrement value 2" << std::flush << std::endl;
}

void increment_value2() {
    std::cout << "Start increment value 2" << std::flush << std::endl;
    for ( int i = 0; i < 50; ++i ) {
        lock_value2.lock();
        value2 ++;
        std::cout << "++value 2 : " << value2 << std::flush << std::endl;
        lock_value2.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
    std::cout << "End increment value 2" << std::flush << std::endl;
}

void increment_both_values() {
    std::cout << "Start increment values 1 and 2" << std::flush << std::endl;
    for ( int i = 0; i < 100; ++i ) {
        std::lock(lock_value2, lock_value1);
        value1 ++; value2 ++;
        std::cout << "++value 1 : " << value1 << ", ++value 2 : " << value2 << std::flush << std::endl;
        lock_value2.unlock();
        lock_value1.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    std::cout << "End increment values 1 and 2" << std::flush << std::endl;
}

int main() {
    std::thread t1(increment_value1_and_decrement_value2);
    std::thread t2(increment_value2);
    std::thread t3(increment_both_values);

    t1.detach(); t2.detach(); t3.detach();
    std::cout << "Processus principal : j'ai detache mes trois processus" << std::flush << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << "J'ai attendu dix secondes. Bye bye !" << std::flush << std::endl;
    return EXIT_SUCCESS;
}