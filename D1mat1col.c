#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define N 1000
 
// This function multiplies A[][] and B[][], and stores
// the result in C[][]
long long int A[N][N],B[N][N],C[N][N];
void *multiply(void *col)
{
    int i, j, k,v;
    v=(int)col;
   // printf("%d\n",v );
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
           // C[i][j] = 0;
                C[j][v] += A[i][v]*B[j][v];
        }
    }
     pthread_exit(0);
}
 
int main()
{
  // To store result
    int i, j;
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
            scanf("%lld",&A[i][j]);
    }
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
            scanf("%lld",&B[i][j]);
    }
    clock_t t;
    t=clock();
    pthread_t tid[N];
    for(i=0;i<N;i++)
    {
        
        pthread_create(&tid[i],NULL,multiply,(void *)i);

       // printf("Thread no.%d with thread id: %llu\n",i,(unsigned long long int)tid );
        //pthread_join(tid,NULL);
        //multiply();
    }
    for(i=0;i<N;i++)
    {
        pthread_join(tid[i],NULL);
    }

     t=clock()-t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("%lf\n",time_taken );
    printf("Result matrix is \n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
           printf("%lld ", C[i][j]);
        printf("\n");
    }
 
    return 0;
}