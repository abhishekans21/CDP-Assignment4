#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#define N 1000
struct data
{
    int row;
    int col;
};
// This function multiplies A[][] and B[][], and stores
// the result in C[][]
long long int A[N][N],B[N][N],C[N][N];
void *multiply(void *arguments)
{
    int i, j, k,r,c;
    struct data *info = (struct data *)arguments;
    r=info->row;
    c=info->col;
    //printf("%d %d\n",r,c);
   // printf("%d\n",v );
    for (i = 0; i < N; i++)
    {
         C[r][c] += A[r][i]*B[i][c];
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
    int count=0,k=0;
    clock_t t;
    t=clock();
    pthread_t tid[N*N];
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            count++;
       
        struct data *info = malloc(sizeof(struct data));
        info->row=j;
        info->col=i;
       // printf("%p\n",info );
        //printf("%d %d\n",info->row,info->col);
        pthread_create(&tid[k],NULL,multiply,(void*)info);
        k++;
        //printf("Thread no.%d with thread id: %llu\n",count,(unsigned long long int)tid );
        }
        //pthread_join(tid,NULL);
        //multiply();
    }
    for(i=0;i<k;i++)
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