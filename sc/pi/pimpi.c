#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include "mpi.h"
#define STD_TAG 0

main(int argc, char **argv) {
{
	int n, myid, numprocs, i;
    double PI25DT = 3.141592653589793238462643;
    double mypi, pi, h, sum, x;
    double tempoI, tempoF;
    
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    
    if(myid==0) {
        tempoI=MPI_Wtime();
    }
    
    if(myid==0) {
       n=atoi(argv[1]);
       printf("\n N=%d",n);
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    h   = 1.0 / (double) n;
    sum = 0.0;
    
    for (i = myid + 1; i <= n; i += numprocs) {
         x = h * ((double)i - 0.5);
         sum += (4.0 / (1.0 + x*x));
    }
    
    mypi = h * sum;
    MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0,MPI_COMM_WORLD);
    
    if (myid == 0) 
         printf("\n\npi is approximately %.16f, Error is %.16f\n",  pi, fabs(pi - PI25DT));
         
    if(myid==0){
        tempoF=MPI_Wtime();
        printf("\n Tempo Inicial:%f\n",fabs(tempoI));
        printf("\n Tempo Final:%f\n",fabs(tempoF));
        printf("\n Tempo Decorrido:%f\n",fabs(tempoI-tempoF));
    }
    
    MPI_Finalize();
    
    return 0;
}
