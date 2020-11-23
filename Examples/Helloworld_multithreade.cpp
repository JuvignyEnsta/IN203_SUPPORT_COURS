#include <iostream>
#include <thread>

// Cette fonction sera appelée par un thread
 void call_from_thread() {
   std::cout << "Hello, World du thread" << std::flush << std::endl;
}

int main() 
{
   // Exécution d'un thread
   std::thread t1(call_from_thread);

   std::cout << "Hello world du processus" << std::flush << std::endl;
   //Join the thread with the main thread
   t1.join();

    return 0;
}

