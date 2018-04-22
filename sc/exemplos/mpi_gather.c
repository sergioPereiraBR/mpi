#include <stdio.h>
#include <mpi.h>
int main(int argc, char* argv[]) {
int rank, tam, tag=99, origem=0, i;
float matsend[4][4]; 
float matrecv[4];
MPI_Status, status;
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &tam);
if (tam == 4) {
for(i=0; i<4; i++)
matrecv[i] = (float)rank*4 + i + 1;
MPI_Gather(matrecv, 4, MPI_FLOAT, matsend, 4, MPI_FLOAT,
 origem, MPI_COMM_WORLD );
// Executa Gather com conteúdo de todos os processos
if( rank == origem )
for(i=0; i<4; i++)
printf(“Resultado: %f %f %f %f\n”, matsend[i][0],
matsend[i][1], matsend[i][2], matsend[i][3]);
 }
else {
if (rank==0)
 printf(“Deve ser executado com número de processos
         igual a 4. Finalizado sem sucesso!\n”);
 }
MPI_Finalize();
return 0;
} 
