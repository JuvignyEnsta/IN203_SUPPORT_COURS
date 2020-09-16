#include <iostream>
#include <cstdio>
#include <mpi.h>
#include <fstream>

int main(int argc, char* argv[])
{
  int size, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  char filename[255];
  sprintf(filename, "Fichier%03d.txt",rank);

  std::ofstream fich(filename);

  fich << "Je suis le proc. " << rank << " sur " << size << std::endl;
  int token = 0;
  if (rank == 0) token = 1;

  fich << "proc n. " << rank << " : token = " << token << std::endl;
  if (size > 1)
  {
      if (rank==0) 
      {
        MPI_Send(&token, 1, MPI_INT, 1, 102, MPI_COMM_WORLD);
      }
      else if (rank == 1)
      {
        MPI_Status status;
        MPI_Recv(&token, 1, MPI_INT, 0, 102, MPI_COMM_WORLD, &status);
      }
  }
  fich << "proc n. " << rank << " : token = " << token << std::endl;

  MPI_Finalize();
  return 1;
}
