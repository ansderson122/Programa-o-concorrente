#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX 100

int *gerar_vetor(int n);


long int soma_vetor(int *vetor, long int TAMANHO) {

    int i;
    long int soma = 0;
    for (i=0;i<TAMANHO;i++) {
        soma = soma + vetor[i];
    }
    return(soma);

}

int main() {

    //Iniciando MPI
    MPI_Init(NULL, NULL);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
    double inicio_rand,fim_rand,tempo_rand,tempo_proc,inicio_proc,fim_proc,tempo_dist,fim_dist;
    int*subvetor = NULL;
    int* vetor = NULL;
    long int i, TAMANHO = 1000 , SUBTAMANHO = (TAMANHO / nprocs);
    

    if(rank == 0){
        vetor = gerar_vetor(TAMANHO);
    }
    
    subvetor = malloc(SUBTAMANHO*sizeof(int));
    MPI_Scatter(vetor,SUBTAMANHO,MPI_INT,subvetor,SUBTAMANHO,MPI_INT,0,MPI_COMM_WORLD);
   

    long int soma;
    soma = soma_vetor(subvetor,SUBTAMANHO);

    double *media;
    double *med = NULL;//med = malloc(sizeof(double));
    long int *resultados_soma = NULL;
    if (rank==0) {
        resultados_soma = malloc(nprocs*sizeof(long int));
        
    }

    
    MPI_Gather(&soma,1,MPI_LONG,resultados_soma,1,MPI_LONG,0,MPI_COMM_WORLD);
    if (rank==0) {
        long int soma_total=0;
        for (i=0; i<nprocs;i++) {
            soma_total = soma_total + resultados_soma[i];
        }
        *media = soma_total/(double)TAMANHO;
    }
    MPI_Scatter(media,1,MPI_DOUBLE,med,1,MPI_DOUBLE,0,MPI_COMM_WORLD);

    double aux;
    for(i=0;i<SUBTAMANHO;i++){
        aux += pow((vetor[i]- (*med)),2);
    }
    
    
    double *resultados = NULL;
    if (rank==0) {
        resultados = malloc(nprocs*sizeof(double));
    }
    MPI_Gather(&aux,1,MPI_DOUBLE,resultados,1,MPI_DOUBLE,0,MPI_COMM_WORLD);

    if (rank==0) {
        double desvio =0;
        for (i=0; i<nprocs;i++) {
            desvio = desvio + resultados[i];
        }
        desvio = desvio / TAMANHO;
        desvio = sqrt(desvio); 
        printf("O devio pradoa e %d \n", desvio);
    }



   
    MPI_Finalize();
    return 0;
}

int *gerar_vetor(int n) {
    int *vetor;
    int i;
    vetor = (int *)malloc(sizeof(float) * n);
    for (i=0;i<n;i++) {
        int num = rand();
        vetor[i] = num;
    }
    return vetor;
}