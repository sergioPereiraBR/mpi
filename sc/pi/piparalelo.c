#include <time.h>
#include <stdio.h>
#include <math.h>
#define NP 150 // Número de processos para o aplicativo

int main( ){
	int rank = 0; // Identificação do processo (máquina)
	double vtempo[NP];
	double tempoMax=0.0;
	double vpi[NP];
	double piFinal=0.0;
	double PI25DT = 3.141592653589793238462643;
	
	printf("\n np eh %u\n",  NP);
	printf("\n\npi eh %.16f\n",  PI25DT);
	
	clock_t tempoInicial, tempoFinal;
	double tempoGasto;
	
	long n, i;
	int v;
	double mypi, pi, h, sum, x;
	
	for(rank=0; rank<NP; rank++){
		
	    tempoInicial = clock();
	    
	    n=0;
		i=0;

	    if (n==0) n=1000;
	    
	    for(v=1; v<=7;v++){
	       //printf("N=%ld ",n);
	       h   = 1.0 / (double) n;
	       sum = 0.0;
	       
	       for (i = rank+1; i <= n; i+=NP) {
	            x = h * ((double)i - 0.5);
	            sum += (4.0 / (1.0 + x*x));
	       }
	       
	       mypi = h * sum;
	       pi = mypi;
	       
	       if(v==4){
	       	  vpi[rank]=pi;
	       	  printf("\nRank [%d]: pi calculado eh aproximadamente na 4a iteração: %.16f, O Erro eh %.16f\n",rank,  vpi[rank], fabs(vpi[rank] - PI25DT));
	       }
	       
	       n*=10;
	    }
	    
	     tempoFinal = clock();
	     tempoGasto =((tempoFinal-tempoInicial)/(double)CLOCKS_PER_SEC);
	     printf("Tempo em segundos: %.6f", tempoGasto);
	     vtempo[rank]=tempoGasto;
	}
	
	for(rank=0; rank<NP;rank++){
		
		if(vtempo[rank]>tempoMax){
			tempoMax=vtempo[rank];
		}
		
		piFinal+=vpi[rank];
	}
	
	 printf("\n\nFinalização dos preocessos:");
	 printf("\npi calculado eh aproximadamente: %.16f, O Erro eh %.16f\n",  piFinal, fabs(piFinal - PI25DT));
	 printf("Maior Tempo em segundos: %.6f\n\n", tempoMax);

	 //system("pause");

	 return 0;
 }
