#include <stdexcept>
#include "thread_extension.h"
#if defined(__WIN32__) || (defined(__WIN64__))
#  include <windef.h>
#  include <winbase.h>
#  include <processthreadsapi.h>
#elif defined(__APPLE__)
#  include <cpuid.h>
#  include <mach/mach.h>
#elif defined(__linux__) || defined (BSD4_4)
//#  include <sched.h>
#  include <pthread.h>
#endif

namespace thread
{
#if defined (__WIN32__) || defined(__WIN64__)
    int current_id()
    {
        return GetCurrentThreadId();
    }

    void set_affinity(std::thread::native_handle_type th, std::uint32_t mask)
    {
        DWORD_PTR lmask = mask;
        int err = SetThreadAffinityMask((HANDLE)th, lmask);
        //if (err <= 0)
        //    throw std::domain_error("Failed to set affinity");
    }

    void set_current_affinity(std::uint32_t mask)
    {
        DWORD_PTR lmask = mask;
        int err = SetThreadAffinityMask(GetCurrentThread(), lmask);
        //if (err <= 0)
        //    throw std::domain_error("Failed to set affinity");
    }

    void set_current_name(const char* thread_name)
    {
        static const DWORD MS_VC_EXCEPTION = 0x406D1388;
#pragma pack(push,8)
        struct THREADNAME_INFO
        {
            DWORD dwType; // must be 0x1000
            LPCSTR szName; // pointer to name (in user addr space)
            DWORD dwThreadID; // thread ID (-1=caller thread)
            DWORD dwFlags; // reserved for future use, must be zero
        } info;
 #pragma pack(pop)
 
        info.dwType = 0x1000;
        info.szName = thread_name;
        info.dwThreadID = -1; //dwThreadID;
        info.dwFlags = 0;
        try
        {
            RaiseException(MS_VC_EXCEPTION, 0, sizeof(info)/sizeof(ULONG_PTR), (ULONG_PTR*)&info);
        }
        catch(std::exception& ex)
        {}
    }

    int get_cpu()
    {
        return (int) GetCurrentProcessorNumber();
    }
#elif defined(__APPLE__)
    int current_id()
    {
        return mach_thread_self();
    }

    void set_affinity(std::thread::native_handle_type th, std::uint32_t mask)
    {
        thread_policy_set(pthread_mach_thread_np(th),THREAD_AFFINITY_POLICY, (integer_t *)&mask, 1);
    }

    void set_current_affinity(std::uint32_t mask)
    {
        set_affinity(pthread_self(), mask);
    }

    void set_current_name(const char* thread_name)
    {
        pthread_setname_np(thread_name);
    }


#  define CPUID(INFO, LEAF, SUBLEAF) __cpuid_count(LEAF, SUBLEAF, INFO[0], INFO[1], INFO[2], INFO[3])

    int get_cpu()
    {
        int CPU;
        uint32_t CPUInfo[4];
        CPUID(CPUInfo, 1, 0);
        /* CPUInfo[1] is EBX, bits 24-31 are APIC ID */
        if ( (CPUInfo[3] & (1 << 9)) == 0) 
        {
          CPU = -1;  /* no APIC on chip */
        }
        else {
          CPU = (unsigned)CPUInfo[1] >> 24;
        }
        if (CPU < 0) CPU = 0;
        return CPU;
    }

#else // Posix GNU threads
    int current_id()
    {
        return 0;
    }

    void set_affinity(std::thread::native_handle_type th, std::uint32_t mask)
    {
        cpu_set_t cpu_set;
        CPU_ZERO(&cpu_set);
        for (int i = 0; i != sizeof(mask) * 8; ++i)
            if ((mask >> i) & 1)
                CPU_SET(i, &cpu_set);
        pthread_setaffinity_np(th, sizeof(cpu_set), &cpu_set);
    }

    void set_current_affinity(std::uint32_t mask)
    {
        set_affinity(pthread_self(), mask);
    }

    void set_current_name(const char* thread_name)
    {
        pthread_setname_np(pthread_self(), thread_name);
    }

    int get_cpu()
    {
        return (int) sched_getcpu();
    }
#endif
}
