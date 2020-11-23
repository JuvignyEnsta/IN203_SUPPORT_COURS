#include <thread>
#include <iostream>
static const int num_threads = 10;

int main() {
  std::thread t[num_threads];

  // Exécution d'un groupe de threads
  //Launch a group of threads
  for (int i = 0; i < num_threads; ++i) {
    t[i] = std::thread([](int i){ std::cout << "Hello from thread " << i << std::endl; }, i);
  }

  std::cout << "Launched from the main\n";

  //Join the threads with the main thread
  for (int i = 0; i < num_threads; ++i) {
    t[i].join();
  }

  return 0;
}
