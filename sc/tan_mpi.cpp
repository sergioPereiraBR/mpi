#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include "mpi.h"

long double power(long double base, int potencia);
long double fatorial(int num);
long double tangente(float num);

int main(int argc, char *argv[]){
	
	int n = 0, ni = 0, i = 0, myid = 0, numprocs = 0;
	
	int grau = 0, minuto = 0, segundo = 0;
	
    double tempoGasto = 0.0, tempoI = 0.0, tempoF = 0.0;
    double tangente = 0.0, tangente_final = 0.0;
	double PI25DT = 3.141592653589793238462643;
	double ang = 0.0, rad = 0.0, x = 0.0;	
	
	long double tang[2];
	long double vtan[2];
	
	tang[0] = 0.0;
	tang[1] = 1.0;
	vtan[0] = 0.0;
	vtan[1] = 0.0;
	
	
    MPI_Init(&argc, &argv); ***** EM CASO DE FALHA NO ARGUMENTO
	//MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    // /*	***** EM CASO DE FALHA NO ARGUMENTO
	
	if(numprocs == 0){
    	numprocs = 1;
	}
	
  	if(argc != 5){
  		printf("\n Erro de argumentos!\n\n USO: tan_mpi ni gg mm ss\n");
  		printf("\n tan_mpi 0 - nome da funao");
  		printf("\n ni      1 - numero de interacoes");
  		printf("\n gg      2 - graus");
  		printf("\n mm      3 - minutos");
  		printf("\n ss      4 - segundos\n");
  		printf("\n\n Argumentos passados:\n\n");
  		
  		int cont;
  		
   		for(cont=0; cont < argc; cont++)
        	printf(" Argumento %d: %s\n", cont,argv[cont]);
        	
		exit(1); 		
	}else{
		// TODO: Criticas de entrada e limites
		ni = atoi(argv[1]);
		grau = atoi(argv[2]);
		minuto = atoi(argv[3]);
		segundo = atoi(argv[4]);	
	}

	//*/	//*****
	/*
	ni = 100;
	grau = 30;
	minuto = 0;
	segundo = 0;
	*/
	
	if(myid == 0){
		printf("\n\t tan_mpi: ni = %d, grau = %d, minuto = %d, segundo = %d\n\n", ni, grau, minuto, segundo);
	}
	
    ang = (double) (grau + (minuto/60.0) + (segundo/3600.0));
   
	x = (double) ang/(180/PI25DT);

	tangente = tan(x);
	
    printf("\n\n\t Tangente do sistema eh %.16f\n", tangente);
	
	printf("\n\t np eh %u\n\n", numprocs);
	
	printf("\n\n\t x %.16f\n", ang);
	
	if(myid == 0){
       n = ni;
    }
    

	if(myid == 0){
        tempoI = MPI_Wtime();
    }


    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
   
    
    for(i = myid+1; i <= n; i += numprocs){
    	
        tang[0] += power((-1), (i-1)) * (1/fatorial(2*i-1)) * power(x, (2*i-1));	
		tang[1] += power((-1), i) * (1/fatorial(2*i)) * power(x, (2*i));
		
    }
    
    
    MPI_Reduce(&tang, &vtan, 1, MPI_LONG_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);    
     
	     
    if(myid == 0){
    	
    	tangente_final = (double) (vtan[0]/vtan[1]);
    	
    	tempoF = MPI_Wtime();
    	
    	printf("\n\n\n\t Tangente calculada eh aproximadamente %.16f, Erro eh %.16f\n\n\n", tangente_final, fabs(tangente_final - tangente));   
        printf("\n\t Tempo Inicial..: %f\n", fabs(tempoI));
        printf("\n\t Tempo Final....: %f\n", fabs(tempoF));
        printf("\n\t Tempo Decorrido: %f\n\n\n", fabs(tempoI - tempoF));
    }
    
    
    MPI_Finalize();
    
    system("pause");
    
    return 0;
}

long double power(long double base, int potencia){
	
	int i = 1;
	long double resultado = base;
	long double x = base;
	
	if(potencia == 0){
		if (base*-1 + base == 0){
			resultado = 1;
		}else{
			resultado = -1;
		}			
	}else{
		while(i < potencia){
			resultado *= x;
			i++;
		}
	}
	
	return resultado;
}

long double fatorial(int num){
	
	long double result = 1;
	int i = 1;
	int x = num;
	
	while(i <= x){
		result *= i;
		i++;
	}
	
	return result;
}
