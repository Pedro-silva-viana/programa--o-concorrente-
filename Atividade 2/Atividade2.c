#include <stdio.h>
#include <omp.h>
#include <time.h>


static long num_steps = 1000000000;
double step;
int main (){
    int i; double x, pi, sum = 0.0;
   step = 1.0/(double) num_steps;
   double inicio = omp_get_wtime();
   #pragma omp parallel num_threads(3) private(x)
   {
       #pragma omp for reduction(+:sum)
       for (i=0;i< num_steps; i++){
           x = (i+0.5)*step;
           sum = sum + 4.0/(1.0+x*x);
       }
   }
   double fim = omp_get_wtime();
   pi = step * sum;
   printf("%.21f\n",pi);
   sum = 0;
   double eficiencia1 = fim-inicio;
   printf("tempo1 = %f\n",fim-inicio);
   inicio = omp_get_wtime();
   for (i=0;i< num_steps; i++){
           x = (i+0.5)*step;
           sum = sum + 4.0/(1.0+x*x);
       }
   fim = omp_get_wtime();
   pi = step * sum;
   double eficiencia2 = fim-inicio;
   double speed_up = eficiencia2/eficiencia1;
   printf("tempo2 = %f\n",fim-inicio);
   printf("speed up = %f\n",eficiencia2/eficiencia1);
   printf("eficiencia = %f\n",speed_up/3);
   return 0;
}

