#include <time.h>
#include <cstdlib>
#include <stdio.h>
#include <math.h>
#define NP 4 // Número de processos para o aplicativo

long double power(long double base, int potencia);
long double fatorial(int num);
long double tangente(float num);

int main(int argc, char *argv[]){
	clock_t tempoInicial = clock();
	clock_t tempoFinal;
	
	int rank = 0; // Identificação do processo (máquina)
	
	int grau = 0.0, minuto = 0.0, segundo = 0.0;
	
	double vtempo[NP];
	double tempoMax=0.0;
	
	double tangente_final = 0.0;
	double PI25DT = 3.141592653589793238462643;
	double tempoGasto;
	double seno;
	double cosseno;
	double tangente;
	
    int n = 0, i = 0, ni = 0; 
    int v;

    double ang, rad = 0.0;

    long double x;
	long double tang[2];
	long double sum_sen = 0;
	long double sum_cos = 0;
	long double vtan[NP][2];
    
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

	printf("\n\t tan_mpi: ni = %d, grau = %d, minuto = %d, segundo = %d\n\n", ni, grau, minuto, segundo);
	
	ang = (double) (grau + (minuto/60.0) + (double) (segundo/3600.0));
   
	x = (double) ang/(180/PI25DT); // passa para radianos


	seno = sin(x);
	cosseno = cos(x);
	tangente = tan(x); // única função a usar math.h para servir de parâmetro no cálculo do erro
	
    printf("\n\n\t Tangente do sistema eh %.16f\n", tangente);
	
	printf("\n\t np eh %u\n",  NP);
	
	for(rank=0; rank<NP; rank++){
			
	    tempoInicial = clock();
	    
	    n=0;
		i=0;

	    if (ni==0) n=1000; else n=ni;
	    
	    for(v=1; v<=7;v++){
	        //printf("N=%ld ",n);
	        
	        tang[0] = 0.0;
			tang[1] = 1.0;
	       
	        for (i = rank+1; i <= n; i+=NP) {
	            tang[0] += power((-1), (i-1)) * (1/fatorial(2*i-1)) * power(x, (2*i-1));	
				tang[1] += power((-1), i) * (1/fatorial(2*i)) * power(x, (2*i));
	        }
	       
	        if(v==4){
	       	    vtan[rank][0] = tang[0];
	       	    vtan[rank][1] = tang[1];
	       	    
	       	    printf("\n\t Rank [%d]: Seno calculado eh aproximadamente na 4a iteracao: %.16f, O Erro eh %.16f\n", rank, (double)vtan[rank][0], (double)fabs(vtan[rank][0]) - seno);
	       	    printf("\n\t Rank [%d]: Cosseno calculado eh aproximadamente na 4a iteracao: %.16f, O Erro eh %.16f\n", rank, (double)vtan[rank][1], (double)fabs(vtan[rank][1]) - cosseno);
	        }
	       
	        //n*=10;
	    }
	    
	    tempoFinal = clock();
	    tempoGasto =((tempoFinal-tempoInicial)/(double)CLOCKS_PER_SEC);
	    printf("\n\t Tempo em segundos: %.6f\n\n", tempoGasto);
	    vtempo[rank]=tempoGasto;
	}
	
	for(rank=0; rank<NP;rank++){
		
		if(vtempo[rank]>tempoMax){
			tempoMax=vtempo[rank];
		}
		
		sum_sen += vtan[rank][0];
		sum_cos += vtan[rank][1];
	}
	
	tangente_final = (double) (sum_sen/sum_cos);

	printf("\n\n\t Finalizacao dos processos:");
	printf("\t Tangente calculada eh aproximadamente %.16f, Erro eh %.16f\n", (double) tangente_final, fabs ((double) tangente_final - tangente));
	printf("\t Maior Tempo em segundos: %.6f\n\n", tempoMax);

	system("pause");

	return 0;
	
}

long double power(long double base, int potencia) {
	
	int i = 1;
	long double resultado = base;
	long double x = base;
	
	if (potencia == 0){
		if (base*-1+base==0) {
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
