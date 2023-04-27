#include <math.h>
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>



#define MAX 500000000


float *gerar_vetor(int n);

void mostrar_vetor(float *v,int tamanho);

void main() {
   
    time_t t;
    srand(time(NULL));
    float *vetor = NULL;
    float n = 0.3578;
    vetor = gerar_vetor(MAX);
    int i = 0;
    float media,desvio;
    double soma = 0,aux;
    // incio do SERIAL ------------------------------------------
    printf("incio da serial \n");
    double inicio = omp_get_wtime();
    
    for(i = 0; i < MAX; i++){
        soma = vetor[i] + soma;
    }media = soma / MAX;

    for(i = 0; i < MAX; i++){
        aux += pow((vetor[i]-media),2);
    }
    desvio =  aux / MAX ;


    printf("O desvio padrao e %.5f \n",desvio);
    double fim = omp_get_wtime();
    double tempo = fim - inicio;
    printf("Tempo  %f \n\n",tempo);


    // fim do SERIAL -------------------------------------------

    // inicio do paralelo ----------------------------------------
    printf("inicio do paralelo \n");
    aux = 0.0;
    double inicio_paralelo = omp_get_wtime();
    float media_paralelo,desvio_paralelo;
    double sum = 0;
    #pragma omp parallel num_threads(4)
	{
		#pragma omp for reduction(+:sum) 
            for(i = 0; i < MAX; i++){
                sum = vetor[i] + sum;
            }
        media_paralelo = sum / MAX;

        #pragma omp for reduction(+:aux) 
            for(i = 0; i < MAX; i++){
                aux += pow((vetor[i]-media),2);
            }
        desvio_paralelo = aux / MAX;
    }       

    
    
    printf("O desvio padrao e %.5f \n",desvio_paralelo);
    double fim_paralelo = omp_get_wtime();
    double tempo_paralelo = fim_paralelo - inicio_paralelo;
    printf("Tempo  %f \n\n",tempo_paralelo);
    
    // fim do paralelo ----------------------------------------

    printf("Execução serial: %.5f \n",tempo);
    printf("Execução paralela: %.5f \n",tempo_paralelo);
    double speedup = tempo/tempo_paralelo;
	printf("Speedup: %.4f\n", speedup);
	printf("Eficiencia: %.4f\n",speedup/4.0);

}

float *gerar_vetor(int n) {
    float *vetor;
    long int i;
    vetor = (float *)malloc(sizeof(float) * n);
    for (i=0;i<n;i++) {
        float num = ((rand() / (float)RAND_MAX));
        vetor[i] = num;
    }
    return vetor;
}

