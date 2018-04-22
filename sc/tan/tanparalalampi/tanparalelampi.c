#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "C:\Program Files (x86)\Microsoft SDKs\MPI\Include\mpi.h"

long double power(long double base, int potencia);
long double fatorial(int num);
long double tangente(float num);

main(int argc, char **argv) {
	
	int n = 0, i = 0, myid = 0, numprocs = 0;
    double ang = 0.0, rad = 0.0;

	double PI25DT = 3.141592653589793238462643;
	double tangente = 0.0;
	double tangente_final = 0.0;
	
	double tempoGasto = 0.0;
	double tempoI = 0.0;
	double tempoF = 0.0;

    long double x = 0.0;
	long double tang[2];
	long double vtan[2];	
	
    MPI_Init(&argc, &argv);
    //MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    //MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    
     	
  	if(argc != 5){
  		printf("Erro de argumentos!\n USO: tangente ni gg mm ss");
		exit(1); 		
	}
	
    ang = (atof(argv[2]) + (atof(argv[3])/60.0) + (atof(argv[4])/3600.0));
   
	x = ang/(180/PI25DT);

	tangente = tan(x);
	
    printf("\n\n\tTangente do sistema eh %.16f\n", tangente);
	
	printf("\n\tnp eh %u\n", numprocs);
	   
    if(myid == 0) {
        //tempoI = MPI_Wtime();
    }
    
    if(myid == 0) {
       n = atoi(argv[1]);
       printf("\n N=%d", n);
    }


    //MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    
    tang[0] = 0.0;
	tang[1] = 1.0;
    
    for (i = myid+1; i <= n; i += numprocs) {
    	
        tang[0] += power((-1), (i-1)) * (1/fatorial(2*i-1)) * power(x, (2*i-1));	
		tang[1] += power((-1), i) * (1/fatorial(2*i)) * power(x, (2*i));
		
    }
    
    
    //MPI_Reduce(&tang, &vtan, 1, MPI_LONG_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);    
     
	     
    if(myid == 0){
    	
    	tangente_final = (double) (vtan[0]/vtan[1]);
    	
    	printf("\n\tTangente calculada eh aproximadamente %.16f, Erro eh %.16f\n",
	          (double) tangente_final, fabs ((double) tangente_final - tangente));
    	
        //tempoF = MPI_Wtime();
        
        printf("\n Tempo Inicial:%f\n", fabs(tempoI));
        printf("\n Tempo Final:%f\n", fabs(tempoF));
        printf("\n Tempo Decorrido:%f\n", fabs(tempoI - tempoF));
    }
    
    
    //MPI_Finalize();
    
    
    return 0;
}

long double power(long double base, int potencia) {
	
	int i = 1;
	long double resultado = base;
	long double x = base;
	
	if (potencia == 0){
		if (base*-1 + base == 0) {
			resultado = 1;
		}else{
			resultado = -1;
		}			
	}else{
		while(i < potencia) {
			resultado *= x;
			i++;
		}
	}
	
	return resultado;
}

long double fatorial(int num) {
	
	long double result = 1;
	int i = 1;
	int x = num;
	
	while (i <= x) {
		result *= i;
		i++;
	}
	
	return result;
}
