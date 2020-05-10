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
#define BUFFER_SIZE 10000

int main(int argc,char *argv[])
{
    // printf("%s",argv[1]) ;
    struct timeval current_time ;
    int fd[2] ;
    char *srcFile = argv[1] ;
    char *dstFile = argv[2] ;
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
        close(fd[WRITE_END]) ;
        printf("inside child process\n") ;
        char data_to_copy[BUFFER_SIZE] ;
        read(fd[READ_END],data_to_copy,BUFFER_SIZE) ;
        close(fd[READ_END]) ;
        FILE *fp;
        fp = fopen(dstFile,"w") ;
        fputs(data_to_copy,fp) ;
        fclose(fp) ;
        exit(0) ;
       
    }
    else if(child>0)
    {
        close(fd[READ_END]) ;
        FILE *fp ;
        fp = fopen(srcFile,"r") ;
        char data_to_read[BUFFER_SIZE] ;
        fseek(fp,0L,SEEK_END) ;
        int size_of_file = ftell(fp) ;
        fseek(fp,0L,SEEK_SET) ;
        printf("Data File Size : %d\n",size_of_file) ;
        
        fgets(data_to_read,size_of_file+1,fp) ;
        printf("Data Read : %s\n",data_to_read) ;
        write(fd[WRITE_END],data_to_read,size_of_file+1) ;
        close(fd[WRITE_END]) ;
        fclose(fp) ;
        wait(NULL) ;
        
    }

    return 0 ;
}