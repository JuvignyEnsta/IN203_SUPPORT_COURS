CC = g++-10
CLANGPP = clang++ -fsanitize=thread
MPICC = mpicc
export OMPI_CC = g++-10
CXX = g++-10
MPICXX = mpic++
export OMPI_CXX = g++-10
LIBMPI = -lmpi
MPIOPT = -oversubscribe

LIBPTHREAD = -lpthread
LIBPSTL    = # -ltbb <= Augustin, à toi de jouer !
