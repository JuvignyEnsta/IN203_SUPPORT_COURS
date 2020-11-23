#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#if defined(_WIN32) || defined(_WIN64)
#  include <processthreadsapi.h>
#  define GETCPU(CPU) {                                \
    CPU = GetCurrentProcessorNumber();                 \
  }
#elif defined(__APPLE__)
#  include <cpuid.h>

#  define CPUID(INFO, LEAF, SUBLEAF) __cpuid_count(LEAF, SUBLEAF, INFO[0], INFO[1], INFO[2], INFO[3])

#  define GETCPU(CPU) {                                \
        uint32_t CPUInfo[4];                           \
        CPUID(CPUInfo, 1, 0);                          \
        /* CPUInfo[1] is EBX, bits 24-31 are APIC ID */\
        if ( (CPUInfo[3] & (1 << 9)) == 0) {           \
          CPU = -1;  /* no APIC on chip */             \
        }                                              \
        else {                                         \
          CPU = (unsigned)CPUInfo[1] >> 24;            \
        }                                              \
        if (CPU < 0) CPU = 0;                          \
      }
#else
#  include <sched.h>
#  define GETCPU(CPU) {                                \
    CPU = sched_getcpu();                              \
  }

#endif

int main(int argc, const char** argv) {
  constexpr unsigned num_threads = 4;
  // A mutex ensures orderly access to std::cout from multiple threads.
  std::mutex iomutex;
  std::vector<std::thread> threads(num_threads);
  for (unsigned i = 0; i < num_threads; ++i) {
    threads[i] = std::thread([&iomutex, i] {
      while (1) {
        {
          int cpu;
          GETCPU(cpu);
          // Use a lexical scope and lock_guard to safely lock the mutex only
          // for the duration of std::cout usage.
          std::lock_guard<std::mutex> iolock(iomutex);

          std::cout << "Thread #" << i << ": on CPU " <<  cpu << std::flush <<  std::endl;          
        }
        // Simulate important work done by the tread by sleeping for a bit...
        std::this_thread::sleep_for(std::chrono::milliseconds(900));
      }
    });
  }

  for (auto& t : threads) {
    t.join();
  }
  return 0;
}
