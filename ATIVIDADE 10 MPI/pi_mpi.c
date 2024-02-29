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
    
    time_t t;
    srand(time(NULL)*rank);
    
    /*
    INICIO
    */
    int pasos = 1000000000;

    double paso = (1/(double)pasos);
    double pi_parcial = 0, x, sum = 0;
    double pi_total = 0;

    for(int i=rank;i<pasos;i+=nprocs){
        x = (i + 0.5)*paso;
        sum = sum + 4.0/(1.0+x*x);
    }
    pi_parcial = paso*sum;
    MPI_Reduce(&pi_parcial,&pi_total,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);

    if (rank==0) {
        printf("Valor de pi: %.6f\n",pi_total);
    }
    /*
    FIM
    */

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