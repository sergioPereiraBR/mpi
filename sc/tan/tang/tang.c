#include <stdio.h>
#include <math.h>

long double power(long double base, int potencia);
long double fatorial(int num);
long double tangente(float num);

int main() {

	float ang = 0.0;
	float rad = 0.0;
	
	printf("Digite o valor do angulo: ");
    scanf("%f", &ang);
   
	rad = ang/(180/3.14159265358979);
	   
	long double teste = tangente(rad);
	printf("\n\n\tCalculo: %.16f\n\n", (double) teste);
	printf("\n\n\tTangente: %.16f\n\n", tan(rad));
	printf("\n\n\tErro: %.16f\n\n", ((double) teste)-tan(rad));
}

long double tangente(float num) {
	long double x = num;
	int inter = 100;
	int n=0;
	long double result_sen = 0;
	long double result_cos = 1;
    
	n++;
	
	while (n < inter) {        
		result_sen += power((-1), (n-1)) * (1/fatorial(2*n-1)) * power(x, (2*n-1));	
		result_cos += power((-1),n) * (1/fatorial(2*n)) * power(x, (2*n));
		n++;
	}
	
	return result_sen/result_cos;
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

