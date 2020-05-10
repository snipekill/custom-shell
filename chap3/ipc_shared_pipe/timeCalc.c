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

#define READ_END 0 
#define WRITE_END 1 

int main(int argc,char *argv[])
{
    // printf("%s",argv[1]) ;
    struct timeval current_time ;
    int fd[2] ;
    if(pipe(fd) == -1)
    {
        printf("Error in creating pipe\n") ;
        exit(0) ;
    }

    pid_t child = fork() ;
    if(child<0)
    {
        printf("error in creating the child process\n") ;
        exit(0) ;
    }
    else if(child == 0)
    {
        close(fd[READ_END]) ;
        printf("inside child process\n") ;
        gettimeofday(&current_time,NULL) ;
        printf("Current Time : %ld\n",current_time.tv_usec) ;
        long int start = current_time.tv_usec ;
        write(fd[WRITE_END],&start,sizeof(start)) ;
        close(fd[WRITE_END]) ;
        argv++ ;
        execvp(argv[0],argv) ;
    }
    else if(child>0)
    {
        close(fd[WRITE_END]) ;
        wait(NULL) ;
        gettimeofday(&current_time,NULL) ;
        // printf("Current Time : %ld\n",end.tv_usec) ;
        // printf("%s\n",ptr) ;
        long int start ;
        read(fd[READ_END],&start,sizeof(start)) ;
        close(fd[READ_END]) ;
        printf("\n\nExecution Time in Milliseconds : %lf\n",(double)(current_time.tv_usec-start)/1000) ;
        
    }

    return 0 ;
}