#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100
#define TAMANHO 10000000

double *gerar_vetor(int n);
float *gerar_vetor_float(float n);
int *gerar_vetor_inteiro(int n);
void mostrar_vetor_inteiro(int *v,int tamanho);
void mostrar_vetor(double *v,int tamanho);

int main() {
    /*
    INICIO
    */
    int p = 4;
    p=p/2;
    int escalar=2;
    float media=0;
    int *vetorf=NULL;
    vetorf = gerar_vetor_inteiro(TAMANHO);
    double variavel=escalar*(vetorf[0]);
    time_t t;
    srand(time(NULL));
    int *vetor = NULL;
    vetor = gerar_vetor_inteiro(TAMANHO);
    double inicio1 = omp_get_wtime();
    for (int i = 0; i < TAMANHO; i++){
        vetorf[i]=escalar*(vetorf[i]);
    }
    for (int i = 0; i < TAMANHO; i++){
        if(variavel<vetorf[i]){
            variavel=vetorf[i];
        }
    }
    double fim1 = omp_get_wtime();
    for (int i = 0; i < TAMANHO; i++){
        vetorf[i]=(vetorf[i])/escalar;
    }
    printf("maior numero float encontrado:%lf\n",variavel);
    variavel=0;
    int veri=0;
    double inicio = omp_get_wtime();
    #pragma omp parallel num_threads(p)
    {
        int id = omp_get_thread_num();
        double num=escalar*(vetorf[id]);
        for(int i = id; i<TAMANHO; i+=p){
            vetorf[i]=escalar*(vetorf[i]);
        }
        for (int i = id; i < TAMANHO; i+=p){
            if(num<vetorf[i]){
                num=vetorf[i];
            }
        }
        #pragma omp critical
        if(veri==0){
            variavel=num;
            veri++;
        }else if(variavel<num){
            variavel=num;
        }
    }
    double fim = omp_get_wtime();
    printf("tempo da operasao com critical operasao:%2f\n",fim-inicio);
    printf("Speedup do critical e:%2f\n",(fim-inicio)/(fim1-inicio1));
    double Speedup=(fim-inicio)/(fim1-inicio1);
    printf("maior numero float encontrado:%lf\n",variavel);
    printf("Eficiencia do critical:%lf\n",Speedup/p);
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