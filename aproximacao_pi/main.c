#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

void main(){
    int num_steps = 100000000;
    double step;
    int i; double x,pi,sum = 0.0;
    step = 1 /(double) num_steps;
    double inicio, fim, tempo_serial,tempo_paralelo; 


    // incio do SERIAL ------------------------------------------
    printf("incio da serial \n");
    inicio = omp_get_wtime();
    for (i=0;i<num_steps;i++){
        x = (i +0.5) * step;
        sum = sum + 4.0/(1.0 + x*x);
    }
    pi = step * sum; 
    fim = omp_get_wtime();
    tempo_serial = fim - inicio;
    printf("o valor de pi e %f \n",pi);
    printf("Tempo  %f \n\n",tempo_serial);

    // fim do SERIAL ------------------------------------------

  
    sum = 0.0;



    // inicio do paralelo ----------------------------------------
    printf("inicio do paralelo \n");
    inicio = omp_get_wtime();

    #pragma omp parallel private(x) num_threads(3)
    {
        #pragma omp for reduction(+:sum)
        for (i=0;i<num_steps;i++){
            x = (i +0.5) * step;
            sum = sum + 4.0/(1.0 + x*x);
        }
       
    } 
    pi  = step * sum; 
    fim = omp_get_wtime();
    tempo_paralelo = fim - inicio;
    printf("o valor de pi e %f \n",pi);
    printf("Tempo  %f \n\n",tempo_paralelo);
        
    // fim do paralelo ----------------------------------------



    printf("Execução serial: %.5f \n",tempo_serial);
    printf("Execução paralela: %.5f \n",tempo_paralelo);
    double speedup = tempo_serial/tempo_paralelo;
	printf("Speedup: %.4f\n", speedup);
	printf("Eficiencia: %.4f\n\n",speedup/4.0);
    


}