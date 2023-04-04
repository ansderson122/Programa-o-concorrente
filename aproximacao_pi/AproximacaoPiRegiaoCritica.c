#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
 
void main(){
    int num_steps = pow(10,9);
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

  
    // inicio do paralelo com região critica 

    printf("inicio do paralelo com região critica \n");
    pi = 0;
    inicio = omp_get_wtime();

    #pragma omp parallel  num_threads(4)

    {
        double sum = 0.0;
        double x;
        #pragma omp for 
            for (i=0;i<num_steps;i++){     
                    x = (i +0.5) * step;
                    sum = sum + 4.0/(1.0 + x*x); 
               
            }
        
        #pragma omp atomic      
        pi += sum * step;

    }


    fim = omp_get_wtime();
    tempo_paralelo = fim - inicio;
    printf("o valor de pi e %f \n",pi);
    printf("Tempo  %f \n\n",tempo_paralelo);



    printf("Execução serial: %.5f \n",tempo_serial);
    printf("Execução paralela: %.5f \n",tempo_paralelo);
    double speedup = tempo_serial/tempo_paralelo;
	printf("Speedup: %.4f\n", speedup);
	printf("Eficiencia: %.4f\n\n",speedup/4.0);
    


}