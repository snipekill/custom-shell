#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

int main()
{
    int pid ;
    pid = fork() ;
    if(pid<0)
    {
        printf("error in creating the child process\n") ;
    }
    else if(pid == 0)
    {
        printf("Child process %d\n",getpid()) ;
        exit(0) ;
        return 0 ;
    }
    else 
    {
        printf("Inside the parent process\n") ;
        printf("Child process id %d\n",pid) ;
        printf("sleeping for 20 seconds child process will turn into zombie\n") ;
        sleep(20) ;
        printf("slept for 20 seconds\n") ;
        wait(NULL) ;
    }
}