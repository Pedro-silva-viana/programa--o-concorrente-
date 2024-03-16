#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX 100
#define TAMANHO 1000000

double *gerar_vetor(int n);
float *gerar_vetor_float(float n);
int *gerar_vetor_inteiro(int n);
void mostrar_vetor_inteiro(int *v,int tamanho);
void mostrar_vetor(double *v,int tamanho);

int main() {
    /*
    INICIO
    */
   MPI_Init(NULL, NULL);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
    time_t t;
    double media = 0;
    double k = 0;
    double variavel = 0;
    int *vetor = NULL;
    int vetor_send[TAMANHO/2];
    if(rank == 0){
        vetor = gerar_vetor_inteiro(TAMANHO);
    }
    MPI_Scatter(vetor, TAMANHO/2, MPI_INT, vetor_send, TAMANHO/2, MPI_INT, 0, MPI_COMM_WORLD);
    for (int i = 0; i < TAMANHO/2; i++){
        variavel+=vetor_send[i];
    }
    long int somatorio[nprocs];
    MPI_Gather(&variavel, 1, MPI_LONG, somatorio, 1, MPI_LONG, 0, MPI_COMM_WORLD);
    if(rank == 0){
      for(int i = 0; i<nprocs; i++){
        media += somatorio[i];
      }  
      media=media/TAMANHO;
    }
    MPI_Scatter(&media, 1, MPI_DOUBLE, &variavel, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    for (int i = 0; i < TAMANHO/2; i++){
        k=k+((vetor_send[i]-variavel)*(vetor_send[i]-variavel));
    }
    double resultado[nprocs];
    MPI_Gather(&k, 1, MPI_DOUBLE, resultado, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    if(rank==0){
        double resultado_final = 0;
        for(int i = 0; i<nprocs; i++){
            resultado_final += resultado[i];
        }
        double desvio = sqrt(resultado_final/TAMANHO);
        printf("O resultado final e:%.2lf\n",desvio);
    }
    /*
    FIM
    */
   MPI_Finalize();
    return 0;
}

double *gerar_vetor(int n) {
    double *vetor;
    int i;
    vetor = (double *)malloc(sizeof(double) * n);
    for (i=0;i<n;i++) {
        double num = (rand() / (float)RAND_MAX);
        vetor[i] = num;
    }
    return vetor;
}

int *gerar_vetor_inteiro(int n) {
    int *vetor;
    int i;
    vetor = (int *)malloc(sizeof(int) * n);
    for (i=0;i<n;i++) {
        int num = (rand() % MAX);
        vetor[i] = num;
    }
    return vetor;
}
float *gerar_vetor_float(float n) {
    float *vetor;
    int i;
    vetor = (float *)malloc(sizeof(float) * n);
    for (i=0;i<n;i++) {
        float num = (rand() % MAX);
        vetor[i] = num;
    }
    return vetor;
}

void mostrar_vetor(double *v,int tamanho) {
    int i;
    for (i=0;i<tamanho;i++) {
        printf("[%.5f]",v[i]);
    }
    printf("\n");
}

void mostrar_vetor_inteiro(int *v,int tamanho) {
    int i;
    for (i=0;i<tamanho;i++) {
        printf("[%d]",v[i]);
    }
    printf("\n");
}