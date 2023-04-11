#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

 
void main(){
    double tempo_paralelo, tempo_serial, inicio,fim;
    long int numero = pow(10,9);
    double soma = 0;

    // incio do SERIAL ------------------------------------------
    printf("incio da serial \n");
    inicio = omp_get_wtime();
    for(long int i = 1;i <= numero; i++){
        if(numero%i == 0){
            soma+=i;
        }
    }
    
    fim = omp_get_wtime();
    tempo_serial = fim - inicio;
    printf("o valor  e %.0f \n",soma);
    printf("Tempo  %f \n\n",tempo_serial);



    // fim do SERIAL ------------------------------------------

  


    // inicio do paralelo ----------------------------------------
    soma = 0;
    printf("inicio do paralelo \n");
    inicio = omp_get_wtime();

     #pragma omp parallel num_threads(4)
    {
        #pragma omp for reduction(+:soma)
        for (long int i = 1; i <= numero; i++){
            if (numero % i == 0){
                soma+=i;
            }
        }
    } 


    fim = omp_get_wtime();
    tempo_paralelo = fim - inicio;
    printf("o valor  e %.0f \n",soma);
    printf("Tempo  %f \n\n",tempo_paralelo);
        
    // fim do paralelo ----------------------------------------



    printf("Execução serial: %.5f \n",tempo_serial);
    printf("Execução paralela: %.5f \n",tempo_paralelo);
    double speedup = tempo_serial/tempo_paralelo;
	printf("Speedup: %.4f\n", speedup);
	printf("Eficiencia: %.4f\n\n",speedup/4.0);
    


}