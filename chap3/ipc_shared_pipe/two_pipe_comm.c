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
#define BUFFER_SIZE 25

int main()
{
    int p1[2],p2[2] ;
    if(pipe(p1) == -1 || pipe(p2) == -1)
    {
        printf("Error in creating pipe\n") ;
        exit(0) ;
    }
    pid_t child = fork();
    if(child == 0)
    {
        close(p1[READ_END]) ;
        close(p2[WRITE_END]) ;
        const char msg[BUFFER_SIZE] = "Hi There" ;
        write(p1[WRITE_END],msg,strlen(msg)+1) ;
        close(p1[WRITE_END]) ;
        char *msg2 ;
        read(p2[READ_END],msg2,25) ;
        close(p2[READ_END]) ;
        printf("SENT FROM THE PARENT PROCESS %s\n",msg2) ;
        exit(0) ;
    }
    else if(child>0)
    {
        close(p1[WRITE_END]) ;
        close(p2[READ_END]) ;
        char msg1[BUFFER_SIZE] ;
        read(p1[READ_END],msg1,BUFFER_SIZE) ;
        close(p1[READ_END]) ;
        printf("SENT FROM THE CHILD PROCESS %s\n",msg1) ;
        char *ptr = msg1 ;
        for(int i=0;ptr[i]!='\0';i++)
        {
            //printf("%d",ptr[i]) ;
            if(ptr[i]>=97&&ptr[i]<=122)
                ptr[i] = ptr[i] - 32 ;
            else if(ptr[i]>=65&&ptr[i]<=90)
                ptr[i] = ptr[i] + 32 ;
            //printf("%d\n",ptr[i]) ;
        }
        write(p2[WRITE_END],ptr,strlen(ptr)) ;
        close(p2[WRITE_END]);
        wait(NULL) ;


    }
    return 0 ;
}