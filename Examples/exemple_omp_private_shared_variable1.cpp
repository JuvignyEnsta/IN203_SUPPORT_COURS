#include <iostream>
#include <omp.h>

int main()
{
    int a = 314;
#   pragma omp parallel
    {
        // Lis un numéro unique pour le thread
        int id = omp_get_thread_num();
        std::cout << "Le thread n." << id << " peut lire la variable a = " << a 
                  << std::flush << std::endl;
        a = 413;
    }
    std::cout << "A la sortie de la région parallele, a vaut " << a << std::flush << std::endl;
    return EXIT_SUCCESS;
}