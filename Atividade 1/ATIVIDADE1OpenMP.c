#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100
#define TAMANHO 9000009

double *gerar_vetor(int n);
float *gerar_vetor_float(float n);
int *gerar_vetor_inteiro(int n);
void mostrar_vetor_inteiro(int *v,int tamanho);
void mostrar_vetor(double *v,int tamanho);

int main() {
    /*
    INICIO
    */
    int a;
    float media=0;
    double *vetorf=NULL;
    vetorf = gerar_vetor(TAMANHO);
    int variavel=0,variavel1;
    scanf("%d",&a);
    time_t t;
    srand(time(NULL));
    int *vetor = NULL;
    vetor = gerar_vetor_inteiro(TAMANHO);
    double inicio = omp_get_wtime();
    #pragma omp parallel num_threads(3)
    {
        #pragma omp for reduction (+:variavel)
        for (int i = 0; i < TAMANHO; i++){
            if(vetor[i]==a){
                variavel++;
            }
        }
    }
    double fim = omp_get_wtime();
    double inicio1 = omp_get_wtime();
    #pragma omp parallel num_threads(1)
    {
        #pragma omp for reduction (+:variavel1)
        for (int i = 0; i < TAMANHO; i++){
            if(vetor[i]==a){
                variavel++;
            }
        }
    }
    double fim1 = omp_get_wtime();
    printf("tempo da primeira operasao:%2f\n",fim-inicio);
    double speed_up=fim1-inicio1/(fim-inicio);
    printf("speed up 1:%2f\n",fim1-inicio1/(fim-inicio));
    printf("eficiencia 1:%2f\n",speed_up/3);
    printf("a quantidade e:%d \n",variavel);
    inicio = omp_get_wtime();
    #pragma omp parallel num_threads(3)
    {
        #pragma omp for reduction (+:media)
            for (int i = 0; i < TAMANHO; i++){
                media=media+vetorf[i];
            }
    }
    fim = omp_get_wtime();
    inicio1 = omp_get_wtime();
    #pragma omp parallel num_threads(1)
    {
        #pragma omp for reduction (+:media)
            for (int i = 0; i < TAMANHO; i++){
                media=media+vetorf[i];
            }
    }
    fim1 = omp_get_wtime();
    printf("o numero da media é:%2f\n",media/TAMANHO);
    printf("tempo da segunda operasao:%2f\n",fim-inicio);
    speed_up=fim1-inicio1/(fim-inicio);
    printf("speed up 2:%2f\n",fim1-inicio1/(fim-inicio));
    printf("eficiencia 2:%2f\n",speed_up/3);
    /*
    FIM
    */
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