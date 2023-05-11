#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

float *gerar_vetor(int n);

int main() {

    //Iniciando MPI
    MPI_Init(NULL, NULL);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
    if (nprocs>3) {
        MPI_Abort(MPI_COMM_WORLD,1);
        MPI_Finalize();
    }
    
    long int i, tamanho = 1000;

    if(rank == 0){
        long int soma_total,soma_total_dobro;
        float* vetor;

        vetor = gerar_vetor(tamanho);

        MPI_Bcast(vetor,tamanho,MPI_LONG,0,MPI_COMM_WORLD);
        MPI_Recv(&soma_total, 1, MPI_LONG, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&soma_total_dobro, 1, MPI_LONG, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Total: %ld\n",soma_total);
        printf("Total do dobro: %ld\n",soma_total_dobro);
    }else if (rank == 1){
        float* vetor = malloc(tamanho*sizeof(float));
        MPI_Bcast(vetor,tamanho,MPI_LONG,0,MPI_COMM_WORLD);

        float soma=0;
        for (i=0; i<tamanho;i++) {
            soma = soma + vetor[i];
        }
        MPI_Send(&soma, 1, MPI_LONG, 0, 0, MPI_COMM_WORLD);
        free(vetor);
    }else if (rank==2){
        float* vetor = malloc(tamanho*sizeof(float));
        MPI_Bcast(vetor,tamanho,MPI_LONG,0,MPI_COMM_WORLD);

        double soma=0;
        for (i=0; i<tamanho;i++) {
            soma = soma + 2*vetor[i];
        }
        MPI_Send(&soma, 1, MPI_LONG, 0, 0, MPI_COMM_WORLD);
        free(vetor);

    }


    MPI_Finalize();
    return 0;
}

float *gerar_vetor(int n) {
    float *vetor;
    int i;
    vetor = (float *)malloc(sizeof(float) * n);
    for (i=0;i<n;i++) {
        float num = (rand() / (float)RAND_MAX);
        vetor[i] = num;
    }
    return vetor;
}