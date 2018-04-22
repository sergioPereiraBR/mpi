#include <time.h>
#include <stdio.h>
#include <math.h>

long double power(long double base, int potencia);
long double fatorial(int num);
long double tangente(float num);

int main( ) {
    clock_t tempoInicial = clock();
	clock_t tempoFinal;
    double tempoGasto;
    
    long n=0, i=0;
    int v;
    double PI25DT = 3.141592653589793238462643;
    
	double mytangente, tangente;

    if (n==0) n = 1000;
    
    float ang, rad = 0.0;
    long double x;
	long double sum_sen = 0.0;
	long double sum_cos = 1.0;
    
	printf("Digite o valor do angulo: ");
    scanf("%f", &ang);
   
	x = ang/(180/PI25DT); // passa para radianos

	tangente = tan(x); // única função a usar math.h para servir de parâmetro no cálculo do erro
	
    printf("\n\nTangente eh %.16f\n", tangente);

    for (v=1; v<=7; v++) {
        printf("\n\n N = %ld ", n);

        sum_sen = 0.0;
        sum_cos = 1.0;

        for (i = 1; i <= n; i++) {           
            sum_sen += power((-1), (i-1)) * (1/fatorial(2*i-1)) * power(x, (2*i-1));	
			sum_cos += power((-1),i) * (1/fatorial(2*i)) * power(x, (2*i));
        }
        
		n++;

        mytangente = sum_sen/sum_cos;
 
        printf("Tangente calculada eh aproximadamente %.16f, Erro eh %.16f\n", mytangente, fabs (mytangente - tangente));

        //n *= 10;
    }

    tempoFinal = clock();
    tempoGasto = ((tempoFinal - tempoInicial) / (double) CLOCKS_PER_SEC);
    printf("\n Tempo em segundos: %5.2f  \n\n", tempoGasto);


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
