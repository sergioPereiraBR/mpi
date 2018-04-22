/* Hello World C Example */
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

int main ( int argc, char **argv )
{
//int argc;
//char **argv;
int tasks;
int eu;

 MPI_Init (&argc, &argv);
 MPI_Comm_size (MPI_COMM_WORLD, &tasks);
 MPI_Comm_rank (MPI_COMM_WORLD, &eu);

 printf("Hello world from process %d of %d\n", eu, tasks);
 MPI_Finalize();

 return (0);

}
