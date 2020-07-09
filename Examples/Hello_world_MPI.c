#include <stdio.h>
#include <mpi.h>

int main(int nargs, char* argv[])
{
    int rank, nbp, lenres;
    char name[4096];
    MPI_Init(&nargs, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nbp);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(name, &lenres);

    printf("Je suis le processus %d sur %d\n", rank,nbp);
    printf("je m'execute sur %s\n", name);

    int tag_to_send = 101*(rank+1);
    printf("tag to send : %d\n", tag_to_send);
    int tag_to_recv;
    MPI_Status status;
    if ( rank == 0 ) {
        MPI_Send(&tag_to_send, 1, MPI_INT, 
                 1, 101, MPI_COMM_WORLD);
        MPI_Recv(&tag_to_recv, 1, MPI_INT, 
                 1, 101, MPI_COMM_WORLD, &status);
    } else {
        MPI_Recv(&tag_to_recv, 1, MPI_INT, 
                 0, 101, MPI_COMM_WORLD, &status);
        MPI_Send(&tag_to_send, 1, MPI_INT, 
                 0, 101, MPI_COMM_WORLD);
    }
    printf("%d : tag received : %d\n", rank,tag_to_recv);
    MPI_Finalize();
    return 0;
}