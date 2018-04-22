#include <stdio.h>
#include "mpi.h"
#define STD_TAG 0

struct {
  int    a; 
  char   b[4];
  double c[2];
} my_struct;

main(int argc, char **argv) {
  int my_rank, n_procs;
  int blocklengths[3];
  MPI_Aint int_length, char_length;
  MPI_Aint displacements[3];
  MPI_Datatype oldtypes[3];
  MPI_Datatype struct_type;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &n_procs);
  if (n_procs != 2) {
    MPI_Finalize();
    if (my_rank == 0)
      printf("Execute o programa com 2 processos!\n");
    exit(0);
  }

  // construir o tipo derivado representando my_struct
  blocklengths[0] = 1;
  blocklengths[1] = 4;
  blocklengths[2] = 2;
  oldtypes[0] = MPI_INT;
  oldtypes[1] = MPI_CHAR;
  oldtypes[2] = MPI_DOUBLE;
  // calcular displacements utilizando MPI_Type_extent
  MPI_Type_extent(MPI_INT, &int_length);
  MPI_Type_extent(MPI_CHAR, &char_length);
  displacements[0] = 0;
  displacements[1] = int_length;
  displacements[2] = int_length + 4 * char_length;
  // em alternativa, calcular displacements utilizando MPI_address
  /*
  MPI_Address(&(my_struct.a), &displacements[0]);
  MPI_Address(&(my_struct.b), &displacements[1]);
  MPI_Address(&(my_struct.c), &displacements[2]);
  displacements[2] -= displacements[0];
  displacements[1] -= displacements[0];
  displacements[0] = 0;
  */
  MPI_Type_struct(3, blocklengths, displacements, oldtypes, &struct_type);
  MPI_Type_commit(&struct_type);

  if (my_rank == 0) {
    // iniciar my_struct
    my_struct.a = 10;
    sprintf(my_struct.b, "mpi");
    my_struct.c[0] = 5.5;
    my_struct.c[1] = 12.4567;
    // enviar my_struct
    MPI_Send(&my_struct, 1, struct_type, 1, STD_TAG, MPI_COMM_WORLD);
  } else {
    // receber em my_struct
    MPI_Recv(&my_struct, 1, struct_type, 0, STD_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Agente 1 recebeu: %d - %s - %f - %f\n", my_struct.a, my_struct.b, 
                                              my_struct.c[0], my_struct.c[1]);
  }

  // libertar o tipo derivado
  MPI_Type_free(&struct_type);
  MPI_Finalize();
}
