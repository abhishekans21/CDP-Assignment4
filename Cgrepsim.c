//Abhishek Tiwari
//B15238
/*while(!happy)
{
	code();
}
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>
struct data
{
	char pattern[100];
	char filename[200];
};
int pos=-1;
void readDirectory(char pat[],char dirString[]);
void *fileinput(void *arguments);
int matching(char pat[],FILE *fp,char file[]);
int strstr1(char buff[],char pat[]);
int check(char pat[]);
void stdinput();
void *dummy(char *arg[])
{
	//printf("%s\n",arg[0] );
	char a[1000];
	strcpy(a,arg[0]);
	strcat(a," ");
	strcat(a,arg[1]);
	//printf("%s\n",arg[1] );
	system(a);
	//char *arg[]=(char *)arguments;
	pthread_exit(0);
}
char *itobase10(char *buf, int value) {
    sprintf(buf, "%d", value);
    return buf;
}
int strstr1(char buff[],char pat[])
{
	int i,blen,plen,c,j;
	blen=strlen(buff);
	plen=strlen(pat);
	for(i=0;i<blen-plen;i++)
	{
		for(j=0;j<plen;j++)
		{
			if(buff[i+j]!=pat[j])
				break;
		}
		if(j==plen)
		{
			return 1;
		}
	}
	return 0;
}
int check(char pat[])
{
	int i;
	for(i=0;i<strlen(pat);i++)
	{
		if(pat[i]=='?')
			return i;
	}
	return -1;
}
void stdinput(char pat[])
{
 	while(1)
 	{
 		matching(pat,stdin,"output");
 	}
}
void *fileinput(void *arguments)
{
	FILE *fp;
	char fname1[1000],fname2[1000],pat[100];
	strcpy(fname1,"/Users/Juno/Documents/5thsem/CDP/week4/files/");
	strcpy(fname2,"/Users/Juno/Documents/5thsem/CDP/week4/output/");
	struct data *info = (struct data *)arguments;
	strcat(fname1,info->filename);
	strcat(fname2,info->filename);
	fp=fopen(fname1,"r");
	strcpy(pat,info->pattern);
	matching(pat,fp,fname2);	
	pthread_exit(0);
}
int matching(char pat[],FILE *fp,char file[])
{
	FILE *fp1;
	fp1=fopen(file,"w+");
	//printf("%s\n",file );
	int i=0,ct=0,ck=0,tot=0;
	char buff[255],ch;
	//pos=check(pat);
	//printf("%d\n",pos );
	while(fgets(buff,sizeof(buff),fp))
	{

		ct++;
		ck=0;
		if(pos==-1)
		{	
			if(strstr1(buff,pat)==1)
			{
				tot++;
				fprintf(fp1,"%d %s",ct,buff);
				ck=1;
			}
		}
		else
		{
			for(i=48;i<=57;i++)
			{
				pat[pos]=i;
				if(strstr1(buff,pat)==1)
				{
					tot++;
					fprintf(fp1,"%d %s",ct,buff);
					ck=1;
					break;
				}
			}
			for(i=97;i<=122;i++)
			{
				pat[pos]=i;
				if(strstr1(buff,pat)==1)
				{
					tot++;
					fprintf(fp1,"%d %s",ct,buff);
					ck=1;
					break;
				}
			}
		}
		if(ck==0)
		{
			int j=0,len;
			char temp[255];
			len=strlen(pat);
			for(i=0;i<len;i++)
			{
				if(pat[i]!='z')
				{	
					temp[j]=pat[i];
					j++;
				}	
			}
			temp[j+1]='\0';
			if(strstr1(buff,temp)==1)
			{
				tot++;
				fprintf(fp1,"%d %s",ct,buff);
				//printf("%d %s\n",ct,buff );
			}
			
		}
		memset(buff,0,255);
	}
	fprintf(fp1,"\nTotal number of lines : %d\n",tot );
	fclose(fp1);
	fclose(fp);
	return 0;
}
void readDirectory(char pat[],char dirString[])    
{
DIR *mydir; 
struct dirent *entry;
mydir = opendir(dirString);  

if(mydir==NULL)
{
fprintf(stderr,"No such file or directory\n");
exit(EXIT_FAILURE);
}   
pthread_t tid[25];
int i=0,n=20,n1=n,cnt=0;
while((entry=readdir(mydir))!=NULL)
{
	if(entry->d_name[0]!='.')
	{
		//printf("%s\n",entry->d_name );
		struct data *info;
		info = (struct data *)malloc(sizeof(struct data));
		strcpy(info->pattern,pat);
		strcpy(info->filename,entry->d_name);
		pthread_create(&tid[i],NULL,fileinput,(void*)info);
		i++;
	}	
}

//int status;
//pthread_t tid;
for(i=0;i<20;i++)
{
	pthread_join(tid[i],NULL);
	//printf("Child with PID %ld exited with status 0x%x.\n",(long)pid,status );
}
/*while((entry=readdir(mydir))!=NULL)
{

  if(entry->d_name[0]!='.')
  {
    fileinput(pat,entry->d_name);
   // printf("%s\n",entry->d_name );
  }
}*/
closedir(mydir);
char num[10000],fName[10000];
int N=20;
int status;
pthread_t tid1[25];
//printf("%d\n",N);
  	for(i=1;i<=N;i++)
  	{
  		itobase10(num,i);
  		strcpy(fName,"/Users/Juno/Documents/5thsem/CDP/week4/output/");
  		strcat(fName,num);
  		char* arg[] = {"cat", fName,NULL};
  		pthread_create(&tid1[i],NULL,dummy,&arg);
  		pthread_join(tid1[i],NULL);
  	}

}
int main(int argc,char *argv[])
{
	pos=check(argv[1]);
	if(argc==2)
	{
		stdinput(argv[1]);
	}
	else if(argc==3)
	{
		readDirectory(argv[1],argv[2]);
	}	
	return 0;
}