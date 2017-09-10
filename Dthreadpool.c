//Abhishek Tiwari
//B15238
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
int row=0,col=1,count=0;
// This function multiplies A[][] and B[][], and stores
// the result in C[][]
long long int A[N][N],B[N][N],C[N][N];
void mul(int r,int c)
{
    int i;
        for (i = 0; i < N; i++)
        {
            C[r][c] += A[r][i]*B[i][c];
        }
}
pthread_mutex_t lock;
void *multiply(void *arguments)
{
    int i, j, k,r,c;
    struct data *info = (struct data *)arguments;

    r=info->row;
    c=info->col;
    // printf("%d %d\n",r,c);
  //      count++;
   // free(info);
    //mul(r,c);
    //count++;
   
   // printf("%d\n",v );
    while(count<N*N && r<N && c<N)
    {
       // mul(r,c);
        for (i = 0; i < N; i++)
        {
            C[r][c] += A[r][i]*B[i][c];
        }
    //    printf("%lld %d %d\n",C[r][c],r,c);
        pthread_mutex_lock(&lock);
        count++;
        
        r=row;
        c=col;
        row++;
        if(row>=N)
        {
            row=row%N;
            col++;
        }   
        pthread_mutex_unlock(&lock);
        printf("");
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
    //int count=0;
    clock_t t;
    t=clock();
    pthread_t tid[N];
    struct data info[N];
    for(i=0;i<N;i++)
    {
       // count++;
       // struct data *info = malloc(sizeof(struct data));
        info[i].row=i;
        info[i].col=0;
        //printf("%d %d\n",info[i].row,info[i].col);
        pthread_create(&tid[i],NULL,multiply,(void*)&info[i]);
        //free(info);
       // count++;
        //printf("Thread no.%d with thread id: %llu\n",count,(unsigned long long int)tid );
        //pthread_join(tid,NULL);
        //multiply();
    }
    for(i=0;i<N;i++)
    {
        pthread_join(tid[i],NULL);
    }
    t=clock()-t;
     double time_taken = ((double)t)/CLOCKS_PER_SEC;
    //printf("%lf\n",time_taken );
    printf("Result matrix is \n");
   for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
           printf("%lld ", C[i][j]);
        printf("\n");
    }

    return 0;
}