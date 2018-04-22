#include "mpi.h"
#define STD_TAG 0
#define ROWS 10
#define COLS 5

main(int argc, char **argv) {
  int i, j, my_rank, n_procs;
  int my_matrix[ROWS][COLS];
  int my_vector[ROWS];
  MPI_Datatype col_matrix;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &n_procs);
  if (n_procs != 2) {
    MPI_Finalize();
    if (my_rank == 0)
      printf("Execute o programa com 2 processos!\n");
    exit(0);
  }

  // iniciar my_matrix
  for (i = 0; i < ROWS; i++)
    for (j = 0; j < COLS; j++)
      my_matrix[i][j] = i + j;

  // construir um tipo derivado com ROWS blocos
  // de 1 elemento separados por COLS elementos
  MPI_Type_vector(ROWS, 1, COLS, MPI_INT, &col_matrix);
  MPI_Type_commit(&col_matrix);

  if (my_rank == 0) {
    // enviar a coluna 1 de my_matrix
    MPI_Send(&my_matrix[0][1], 1, col_matrix, 1, STD_TAG, MPI_COMM_WORLD);
    printf("Agente 0 enviou: ");
    for(i = 0; i < ROWS; i++)
      printf("%d ", my_matrix[i][1]);
    printf("\n");
    // enviar a coluna 2 de my_matrix
    MPI_Send(&my_matrix[0][2], 1, col_matrix, 1, STD_TAG, MPI_COMM_WORLD);
    printf("Agente 0 enviou: ");
    for(i = 0; i < ROWS; i++)
      printf("%d ", my_matrix[i][2]);
    printf("\n");
  } else {
    // receber na coluna 3 de my_matrix
    MPI_Recv(&my_matrix[0][3], 1, col_matrix, 0, STD_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Agente 1 recebeu: ");
    for(i = 0; i < ROWS; i++)
      printf("%d ", my_matrix[i][3]);
    printf("\n");
    // receber em my_vector
    MPI_Recv(&my_vector, ROWS, MPI_INT, 0, STD_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Agente 1 recebeu: ");
    for(i = 0; i < ROWS; i++)
      printf("%d ", my_vector[i]);
    printf("\n");
  }

  // libertar o tipo derivado
  MPI_Type_free(&col_matrix);
  MPI_Finalize();
}