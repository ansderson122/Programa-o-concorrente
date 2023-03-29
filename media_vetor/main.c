#include <omp.h>
#include <stdio.h>
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

    // incio do SERIAL ------------------------------------------
    printf("incio da serial \n");
    double inicio = omp_get_wtime();
    float media;
    double soma = 0;
    for(i = 0; i < MAX; i++){
        soma = vetor[i] + soma;
    }
    printf("soma %.5f \n",soma);
    media = soma / MAX;
    printf("A media e %.5f \n",media);
    double fim = omp_get_wtime();
    double tempo = fim - inicio;
    printf("Tempo  %f \n\n",tempo);


    // fim do SERIAL -------------------------------------------

    // inicio do paralelo ----------------------------------------
    printf("inicio do paralelo \n");
    double inicio_paralelo = omp_get_wtime();
    float media_paralelo;
    double sum = 0;
    #pragma omp parallel num_threads(4)
	{
		#pragma omp for reduction(+:sum) 
            for(i = 0; i < MAX; i++){
                sum = vetor[i] + sum;
            }

    }
    printf("soma %.5f \n",sum);
    media_paralelo = sum / MAX;
    printf("A media e %.5f \n",media_paralelo);
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

void mostrar_vetor(float *v,int tamanho) {
    int i;
    for (i=0;i<tamanho;i++) {
        printf("[%.5f]",v[i]);
    }
    printf("\n");
}