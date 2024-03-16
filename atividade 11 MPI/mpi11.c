 #include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#define MAX 100
int *gerar_vetor_binario(int *vetor,int n);
int main() {
    
    //Iniciando MPI
    MPI_Init(NULL, NULL);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
    time_t t;
    int vetor[MAX];
    int soma = 0;
    long int do_soma = 0;
    if(rank == 0){
        *gerar_vetor_binario(vetor,MAX);
        MPI_Bcast(vetor,MAX,MPI_INT,0,MPI_COMM_WORLD);
    }else{
        MPI_Bcast(vetor,MAX,MPI_INT,0,MPI_COMM_WORLD);
    }
    if(rank==1){
        //soma = 0
        for(int i=0;i<MAX;i++){
            soma += vetor[i];
        }
        MPI_Send(&soma,1,MPI_INT,0,0,MPI_COMM_WORLD);
    }else if(rank == 2){
        for(int i=0;i<MAX;i++){
            //soma
            do_soma += 2*vetor[i];
        }
        MPI_Send(&do_soma,1,MPI_LONG,0,0,MPI_COMM_WORLD);
    }
    if(rank == 0){
        MPI_Recv(&soma,1,MPI_INT,1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        MPI_Recv(&do_soma,1,MPI_LONG,2,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("A soma e:%d\n",soma);
        printf("A soma dobrada e:%ld\n",do_soma);
    }
    /*
    FIM
    */
    MPI_Finalize();
    return 0;
}

int *gerar_vetor_binario(int *vetor,int n) {
  int i;
  for (i=0;i<n;i++) {
    int num = rand() %20;
    vetor[i] = num;
  }
  return vetor;
}