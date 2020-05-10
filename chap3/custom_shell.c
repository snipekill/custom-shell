#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include <unistd.h>
#include<sys/time.h>
#include<sys/mman.h>
#include<sys/wait.h>

#define MAXLINE 80

void parse(char *inp,char **args,int *argc,int *command_type,char *fileName)
{
    int j=0 ;
    char newString[MAXLINE/2+1] ;
    for(int i=0;1==1;i++)
    {
        // printf("new char %c : \n",inp[i]) ;
        if(inp[i]==' '||inp[i]=='\0'||inp[i]=='\n')
        {
            newString[j]='\0';
            args[*argc] = (char *)calloc(j+1,sizeof(newString[j])) ;
            strcpy(args[*argc],newString) ;
			if(strcmp("exit",args[0])==0)
			{
				*command_type = 4;
				break ;
			}
			if(strcmp("!!",args[0])==0)
			{
				*command_type = 5 ;
				break ;
			}
			else if(strcmp(">",args[*argc])==0)
			{
				*command_type = 2 ;
			}
			else if(strcmp("<",args[*argc])==0)
			{
				*command_type = 3 ;
			}
			else if(*command_type == 2 || *command_type == 3)
			{
				printf("FILENAME RE : %s\n",args[*argc]) ;
				strcpy(fileName,args[*argc]) ;
				break ;
			}
            (*argc)++ ;
            j=0;
            if(inp[i]=='\0' || inp[i]=='\n')
                break;
        }
        else
        {
            newString[j]=inp[i];
            j++;
        }
    }
}

int main(void)
{
    char *args[MAXLINE/2+1] ;
    int should_run = 1 ;
    char his_inp[MAXLINE] ;
	his_inp[0] = '\0' ;
	int command_type = 1 ;
    while (should_run)
    {
        printf("osh>");
        fflush(stdout) ;
        int argc = 0 ;
        char inp[MAXLINE] ;
		command_type = 1 ;
		char fileName[20] ;
        fgets(inp,MAXLINE,stdin) ;
        parse(inp,args,&argc,&command_type,fileName) ;
		fileName[0] = '\0' ;
        if(command_type == 4)
            break ;
        else if(command_type == 5)
        {
            if(his_inp[0]=='\0')
            {
                printf("No history available\n") ;
                continue ;
            }
            else
            {
				argc = 0 ;
                parse(his_inp,args,&argc,&command_type,fileName) ;
            }
        }
		else
			strcpy(his_inp,inp) ;
        int fwait = 1;
        if(strcmp("&",args[argc-1])==0)
        {
            fwait = 0 ;
            argc --;
        }

        args[argc] = NULL ;
        // for(int i=0;i<=argc;i++)
        // {
        //     printf("%s",args[i]) ;
        // }
        printf("Command Type : %d\n",command_type) ;
		printf("File Name : %s\n",fileName) ;
        pid_t child = fork() ;

        if(child == 0)
        {
			if(command_type == 2 && fileName[0]!='\0')
			{
				int fd = open(fileName,O_CREAT | O_RDWR) ;
				dup2(fd,STDOUT_FILENO) ;
			}
            if(execvp(args[0],args)!=-1)
				exit(1) ;
			else printf("Execution Failed\n") ;
			exit(0) ;
        }
        else if(child>0)
        {
            // printf("wait hai kya %d\n",fwait) ;
             if(fwait)
                wait(NULL) ;
			
        }
        // printf("%s\n",*args) ;
    }
   // wait(NULL) ;
    
}