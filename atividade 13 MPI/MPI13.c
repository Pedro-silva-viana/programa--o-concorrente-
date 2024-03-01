#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#define MAX 100
int *gerar_vetor_binario(int n);
int main() {
    
    //Iniciando MPI
    MPI_Init(NULL, NULL);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
    
    time_t t;
    int num = 0,numb=0;
    int *gerar_vetor = (int*)malloc(sizeof (int) *MAX);
    srand(time(NULL)*rank);
    if(rank==0){
      gerar_vetor = gerar_vetor_binario(MAX);
      MPI_Bcast(gerar_vetor,MAX,MPI_INT,0,MPI_COMM_WORLD);
    }
    else{
      MPI_Bcast(gerar_vetor,MAX,MPI_INT,0,MPI_COMM_WORLD);
      printf("Recebido pelo Rank:%d\n",rank);
    }
    for(int i=rank;i<MAX;i+=nprocs){
      if(gerar_vetor[i]==1){
        num++;
      }
    }
    MPI_Reduce(&num,&numb,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    if(rank==0){
      if(numb%2==0){
        printf("quantidade de 1s par:coreto\n");
      }else{
        printf("incoreto\n");
      }
    }
    /*
    FIM
    */
    MPI_Finalize();
    return 0;
}

int *gerar_vetor_binario(int n) {
  int *vetor;
  int i; 
  vetor = (int *)malloc(sizeof(int) * n);
  for (i=0;i<n;i++) {
    int num = rand() % 2;
    vetor[i] = num;
  }
  return vetor;
}