#include <stdio.h>
#include "mpi.h"
int main(int argc, char **argv)
{
  MPI_Init(&argc, &argv);
  printf("Alô Mundo!");
  MPI_Finalize();
  return 0;
}