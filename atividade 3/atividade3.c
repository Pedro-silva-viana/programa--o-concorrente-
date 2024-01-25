#include "stdio.h"
#include "omp.h"
#include "time.h"
int main(){
    unsigned long long int variavel=1000000000;
    unsigned long long int soma=0;
    float inicio, fim;
    long a[2];
    inicio=omp_get_wtime();
    for(int i=1;i<=variavel;i++){
        if(variavel%i==0){
            soma=soma+i;
        }
    }
    fim=omp_get_wtime();
    printf("normal:%f\n",fim-inicio);
    printf("%llu\n",soma);
    soma=0;
    inicio=omp_get_wtime();
    #pragma omp parallel num_threads(3)
    {
        #pragma omp for reduction(+:soma)
        for(int i=1;i<=variavel;i++){
        if(variavel%i==0){
            soma=soma+i;
        }
    }
    }
    fim=omp_get_wtime();
    printf("parallel:%f\n",fim-inicio);
    printf("parallel:%llu\n",soma);
    soma=0;
    inicio=omp_get_wtime();
    #pragma omp parallel num_threads(3)
    {
        int id = omp_get_thread_num();
        long int somar = 0;
        for(int i=id;i<variavel;i=i+3){
            if(variavel%(i+1)==0){
                somar=somar+i;
            }
        }
        #pragma omp critical
        soma = soma+somar; 
    }
    fim=omp_get_wtime();
    printf("parallel critical:%f\n",fim-inicio);
    printf("%llu\n",soma);
    soma = 0;
    inicio=omp_get_wtime();
    #pragma omp parallel num_threads(3)
    {
        int id = omp_get_thread_num();
        long int somar = 0;
        for(int i=id;i<variavel;i=i+3){
            if(variavel%(i+1)==0){
                somar=somar+i;
            }
        }
        #pragma omp atomic
        soma = soma+somar; 
    }
    fim=omp_get_wtime();
    printf("parallel atomic:%f\n",fim-inicio);
    printf("%llu\n",soma);
    return 0;
}