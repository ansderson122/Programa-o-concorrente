#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


float *gerar_vetor(int n);

void mostrar_vetor(float *v,int tamanho);


 
void main(){
    long int tamanhoVetor = pow(10,9);
    time_t t;
    srand(time(NULL));
    float *vetor = NULL;
    float x = 0.3578;
    vetor = gerar_vetor(tamanhoVetor);
    double tempo_paralelo, tempo_serial, inicio,fim;
    
    int ocorrencias;
    // incio do SERIAL ------------------------------------------
    printf("incio da serial \n");
    inicio = omp_get_wtime();

    for(long int i = 0; i < tamanhoVetor; i++){
        if(vetor[i] == x ){
            ocorrencias++;
        }
    
    }
    

    fim = omp_get_wtime();
    tempo_serial = fim - inicio;
    printf("o numero de ocorrencias de x: %i \n",ocorrencias);
    printf("Tempo  %f \n\n",tempo_serial);



    // fim do SERIAL ------------------------------------------

  


    // inicio do paralelo ----------------------------------------
    ocorrencias = 0;
    printf("inicio do paralelo \n");
    inicio = omp_get_wtime();

    #pragma omp parallel num_threads(4)
        {
            #pragma omp for reduction(+:ocorrencias)
            for (long int i = 0; i < tamanhoVetor; i++){
                if (vetor[i] == x){
                    ocorrencias++;
                }
            }
        } 



    fim = omp_get_wtime();
    tempo_paralelo = fim - inicio;
    printf("o numero de ocorrencias de x: %i \n",ocorrencias);
    printf("Tempo  %f \n\n",tempo_paralelo);
        
    // fim do paralelo ----------------------------------------



    printf("Execução serial: %.5f \n",tempo_serial);
    printf("Execução paralela: %.5f \n",tempo_paralelo);
    double speedup = tempo_serial/tempo_paralelo;
	printf("Speedup: %.4f\n", speedup);
	printf("Eficiencia: %.4f\n\n",speedup/4.0);
    


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