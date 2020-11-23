#include <iostream>
#include <thread>

int main() 
{
   // Exécution d'un thread
   std::thread t1([](){std::cout << "Hello, World du thread" << std::flush << std::endl;});

   std::cout << "Hello world du processus" << std::flush << std::endl;
   //Join the thread with the main thread
   t1.join();

    return 0;
}

