#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h> 
#include <sys/stat.h>
void *thfunc(void *a){

         //printf("thread %lld\n", (long long int)pthread_self());
         pthread_exit(0);
}

void *pfunc(pid_t mypid)
{
	     int stat;
         waitpid(mypid,&stat,0);
         //printf("process %ld\n", (long)mypid);
         exit(0);
}


int main()
{
  int i,n=10000;
  pid_t pids[n];
  pthread_t tids[n];
  int x;
  printf("Enter (1) for forking OR (0) for threading\n");
  scanf("%d",&x);
if(x==1)
{
  for (i = 0; i < n; ++i) 
  {
    if ((pids[i] = fork()) < 0) 
	  {
    	perror("fork");
    	abort();
  	  } 
    else if (pids[i] == 0) 
      {
        pfunc(getpid());
        exit(0);
      }
	  }
}
else if(x==0)
{


   for(i=0;i<n;i++)
	   pthread_create(&tids[i],NULL, thfunc, NULL);

   for(i=0;i<n;i++)   
	   pthread_join(tids[i],NULL);

}
else 
  printf("Invalid input\n");

return 0;
}