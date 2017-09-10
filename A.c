//Abhishek Tiwari
//B15238
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int level=2,i,stat,stat2;
	pid_t pid,pid2,pid1;
	for(i=0;i<level;i++)
	{
		pid=fork();
		if(pid!=0) pid2=fork();
		if(pid && pid2)
			{
				pid1=getpid();
				printf("Parent : %ld\n",(long)pid1);
				printf("Child 1 : %ld  Child 2 : %ld \n",(long)pid,(long)pid2);
				break;
			}
	}
	waitpid(pid,&stat,0);
    waitpid(pid2,&stat2,0);
	//wait(10000000);

	return 0;
}