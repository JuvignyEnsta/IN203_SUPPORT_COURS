#include <iostream>
#include <cstdint>
#include <cmath>
#include <vector>
#include <omp.h>

std::uint64_t syracuse(std::uint64_t u0)
{
    std::uint64_t un = u0;
    std::uint64_t cpteur = 0;
    do
    {
        un = (un%2 == 0 ? un / 2 : (3*un+1)/2);
        cpteur ++;
    } while (un != 1);
    return cpteur;
}

int main()
{
    const std::uint64_t N = 100000000;
    std::vector<std::uint64_t> lgth_fly(N);
    double t1 = omp_get_wtime();
#   pragma omp parallel for
    for ( std::uint64_t i = 3; i < N; ++i )
    {
        lgth_fly[i-3] = syracuse(i);
    }
    double t2 = omp_get_wtime();
    std::cout << "Temps parallélisation statique : " << t2-t1 << " secondes." << std::endl << std::flush;

    t1 = omp_get_wtime();
#   pragma omp parallel for schedule(dynamic,10000)
    for ( std::uint64_t i = 3; i < N; ++i )
    {
        lgth_fly[i-3] = syracuse(i);
    }
    t2 = omp_get_wtime();
    std::cout << "Temps parallélisation dynamique : " << t2-t1 << " secondes." << std::endl << std::flush;

    return EXIT_SUCCESS;
}