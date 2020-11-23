#include <omp.h>
#include <algorithm>
#include <iostream>

int main()
{
  const int n = 4096;
  double a[n];
  int i, i_min, i_max, rang, nb_taches;
# pragma omp parallel private(rang, nb_taches, i_min, i_max)
  {
      rang = omp_get_thread_num();
      i_min = n; i_max = 0;
#     pragma omp for nowait //schedule(static, n/nb_taches) nowait
      for ( i = 0; i < n; ++i) {
          a[i] = 92290 + double(i);
          i_min = std::min(i,i_min); i_max = std::max(i,i_max);
      }
      std::cout << "rang : " << rang << ": i_min = " << i_min
                << ", i_max = " << i_max << std::flush << std::endl;
  }
  return EXIT_SUCCESS;
}