#include Make_linux.inc
include Make_msys2.inc
#include Make_osx.inc

CXXFLAGS = -std=c++11 -fPIC
CXXFLAGS17 = -std=c++17 -fPIC
ifdef DEBUG
CFLAGS   = -g -O0 -Wall -fbounds-check -pedantic
CXXFLAGS += ${CFLAGS} -D_GLIBCXX_DEBUG
CXXFLAGS17 += ${CFLAGS} -D_GLIBCXX_DEBUG
else
CFLAGS = -O3 -march=native
CXXFLAGS += ${CFLAGS}
CXXFLAGS17 += ${CFLAGS} 
endif

ALL= Hello_world_MPI.exe EchangeDeuxProcs.exe \
     Helloworld_multithreade.exe Helloworld_multithreade_lambda_function.exe \
     Helloworld_ten_threads.exe test_hardware_concurrency.exe \
     exemple_detach_thread.exe get_cpu_for_threads.exe \
     ref_et_cref_pour_les_threads.exe example_data_race_read_write.exe \
     exemple_set_affinity.exe exemple_interblocage.exe exemple_interblocage_correction.exe \
     exemple_thread_atomic.exe \
     exemple_omp_parallel_region.exe exemple_omp_private_shared_variable1.exe\
     exemple_omp_private_shared_variable2.exe exemple_omp_private_shared_variable3.exe\
     exemple_omp_reduction_numthreads.exe exemple_omp_for_static.exe \
     exemple_omp_for_dynamic.exe \
     exemple_stl_parallel.exe

default:	help

all: $(ALL)

clean:
	@rm -fr *.o *.exe *~ *.tga

#%.exe: %.cpp
#	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIB)

Hello_world_MPI.exe : Hello_world_MPI.c
	$(MPICC) $(CFLAGS) -o $@ $^ $(LIBMPI)

EchangeDeuxProcs.exe : EchangeDeuxProcs.cpp
	$(MPICXX) $(CXXFLAGS) -o $@ $^ $(LIBMPI)

Helloworld_multithreade.exe : Helloworld_multithreade.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBPTHREAD)

Helloworld_multithreade_lambda_function.exe : Helloworld_multithreade_lambda_function.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBPTHREAD)

Helloworld_ten_threads.exe :	Helloworld_ten_threads.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBPTHREAD)

test_hardware_concurrency.exe : test_hardware_concurrency.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBPTHREAD)

exemple_detach_thread.exe : exemple_detach_thread.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBPTHREAD)

get_cpu_for_threads.exe : get_cpu_for_threads.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBPTHREAD)

exemple_stl_parallel.exe : exemple_stl_parallel.cpp
	$(CXX) $(CXXFLAGS17) -o $@ $^ $(LIBPTHREAD) $(LIBPSTL)

ref_et_cref_pour_les_threads.exe : ref_et_cref_pour_les_threads.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBPTHREAD)

exemple_set_affinity.exe : exemple_set_affinity.cpp thread_extension.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBPTHREAD)

exemple_interblocage.exe : exemple_interblocage.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBPTHREAD)

exemple_interblocage_correction.exe : exemple_interblocage_correction.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBPTHREAD)

exemple_thread_atomic.exe : exemple_thread_atomic.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBPTHREAD)

exemple_omp_parallel_region.exe : exemple_omp_parallel_region.cpp
	$(CXX) $(CXXFLAGS) -fopenmp -o $@ $^ $(LIBPTHREAD)

exemple_omp_private_shared_variable1.exe : exemple_omp_private_shared_variable1.cpp
	$(CXX) $(CXXFLAGS) -fopenmp -o $@ $^ $(LIBPTHREAD)	

exemple_omp_private_shared_variable2.exe : exemple_omp_private_shared_variable2.cpp
	$(CXX) $(CXXFLAGS) -fopenmp -o $@ $^ $(LIBPTHREAD)	

exemple_omp_private_shared_variable3.exe : exemple_omp_private_shared_variable3.cpp
	$(CXX) $(CXXFLAGS) -fopenmp -o $@ $^ $(LIBPTHREAD)	

exemple_omp_reduction_numthreads.exe : exemple_omp_reduction_numthreads.cpp
	$(CXX) $(CXXFLAGS) -fopenmp -o $@ $^ $(LIBPTHREAD)	

exemple_omp_for_static.exe : exemple_omp_for_static.cpp
	$(CXX) $(CXXFLAGS) -fopenmp -o $@ $^ $(LIBPTHREAD)	

exemple_omp_for_dynamic.exe : exemple_omp_for_dynamic.cpp
	$(CXX) $(CXXFLAGS) -fopenmp -o $@ $^ $(LIBPTHREAD)	

example_data_race_read_write.exe : example_data_race_read_write.cpp
	$(CLANGPP)  -std=c++14  -O1 -o $@ $^ $(LIBPTHREAD)


help:
	@echo "Available targets : "
	@echo "    all            : compile all executables"
	@echo "    matvec.exe     : compile matrix vector product executable"
	@echo "    Mandelbrot.exe : compile Mandelbrot set computation executable"
	@echo "Add DEBUG=yes to compile in debug"
	@echo "Configuration :"
	@echo "    CXX      :    $(CXX)"
	@echo "    CXXFLAGS :    $(CXXFLAGS)"
