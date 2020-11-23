#include <iostream>
#include <omp.h>

int main() {
    int s = 0;
#   pragma omp  parallel reduction(+:s) num_threads(2)
    {
        s = omp_get_thread_num()+1;
    }
    std::cout << "s = " << s << std::endl;
    return EXIT_SUCCESS;
}
