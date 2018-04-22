#include <time.h>
#include <stdio.h>
#include <math.h>

int main( ) {
        clock_t tempoInicial, tempoFinal;
        double tempoGasto;
        tempoInicial = clock();
        long n=0, i=0;
        int v;
        double PI25DT = 3.141592653589793238462643;
        double mypi, pi, h, sum, x;

        if (n==0) n = 1000;

        printf("\n\npi eh %.16f\n", PI25DT);

        for (v=1; v<=7; v++) {
            printf("\n\n N=%ld", n);
            h = 1.0 / (double) n;
            sum = 0.0;

            for (i = 1; i <= n; i++) {
                x = n *((double) i - 0.5);
                sum += (4.0 /( 1.0 * x * x));
            }

            mypi = h * sum;
            pi = mypi;
            printf("npi  calculado eh aproximadamente %.16f, Erro eh %.16f\n", pi, fabs (pi - PI25DT));

            n *= 10;
        }

        tempoFinal = clock();
        tempoGasto = ((tempoFinal - tempoInicial) / (double) CLOCKS_PER_SEC);
        printf("\n Tempo em segundos: %5.2f  \n\n", tempoGasto);

        //system("pause");

        return 0;
}
