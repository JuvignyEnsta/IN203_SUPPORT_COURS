#include <iostream>
#include <iomanip>
#include <omp.h>

int main()
{
    int p;
    // Teste si on est dans une région parallèle
    p = omp_in_parallel();
    std::cout << "Dans une region parallele ? " << std::boolalpha << (p!=0) << std::flush << std::endl;
#pragma omp parallel
{
    // Teste si on est dans une région parallèle
    int p2 = omp_in_parallel();
    std::cout << "Dans une region parallele ? " << std::boolalpha << (p2!=0) << std::flush << std::endl;
}
    return EXIT_SUCCESS;
}