#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


#define MAX 100


int *gerar_vetor_inteiro(int n);


 
void main(){
    long int tamanhoVetor = pow(10,9);
    time_t t;
    srand(time(NULL));
    int *vetor = NULL;
    int x = 3;
    vetor = gerar_vetor_inteiro(tamanhoVetor);
    double tempo_paralelo, tempo_serial, inicio,fim;
    
    long int ocorrencias;
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
            int tem = 0;
            #pragma omp for 
            for (long int i = 0; i < tamanhoVetor; i++){
                if (vetor[i] == x){
                    tem++;
                }
            }

            #pragma omp atomic
                ocorrencias += tem; 
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


int *gerar_vetor_inteiro(int n) {
    int *vetor;
    long int i;
    vetor = (int *)malloc(sizeof(int) * n);
    for (i=0;i<n;i++) {
        int num = (rand() % MAX);
        vetor[i] = num;
    }
    return vetor;
}