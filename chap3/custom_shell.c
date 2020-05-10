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

void parse(char *inp,char **args,int *argc)
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
    int history =0 ;
    while (should_run)
    {
        printf("osh>");
        fflush(stdout) ;
        int argc = 0 ;
        char inp[MAXLINE] ;
        fgets(inp,MAXLINE,stdin) ;
        strcpy(his_inp,inp) ;
        parse(inp,args,&argc) ;
        if(strcmp("exit",args[0])==0)
        {
            break ;
        }
        if(strcmp("!!",args[0])==0)
        {
            if(history == 0)
            {
                printf("No history available\n") ;
                continue ;
            }
            else
            {
                parse(his_inp,args,&argc) ;
            }
            
            
        }
        history = 1;
        int fwait = 1;
        if(args[argc-1][0]=='&')
        {
            fwait = 0 ;
            argc --;

        }
        args[argc] = NULL ;
        for(int i=0;i<=argc;i++)
        {
            printf("%s",args[i]) ;
        }
        if(history == 0)
                history=1;
        pid_t child = fork() ;
        if(child == 0)
        {
            // printf("haha %s\n",args[1]);
            // char t[10] = "ls" ;
            // char *p[0] ;
            // p = t;
            if(args[argc-1][0]=='&')
                {
                    fwait = 0 ;
                    argc --;

                }
                
            
            execvp(args[0],args) ;
        }
        else if(child>0)
        {
            printf("wait hai kya %d\n",fwait) ;
             if(fwait)
                wait(NULL) ;
        }
        // printf("%s\n",*args) ;
    }
    wait(NULL) ;
    
}