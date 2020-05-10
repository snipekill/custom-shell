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

#define BUFFER_SIZE 4096 

int main(int argc,char *argv[])
{
    int num = atoi(argv[1]) ;
    if(num<0)
    {
        printf("Invalid Input \n") ;
        exit(0) ;
    }
    const char *name = "OS" ;
    int fd = shm_open(name,O_CREAT | O_RDWR,0666) ;
    ftruncate(fd,BUFFER_SIZE) ;
    char *ptr = (char *)mmap(0,BUFFER_SIZE,PROT_READ| PROT_WRITE,MAP_SHARED,fd,0) ;
    pid_t child = fork() ;
    int terminating_num = -1 ;
    if(child<0)
    {
        printf("Error in creating the child process") ;
    }
    else if(child == 0)
    {
        printf("num : %d\n",num) ;
        int size_int = sizeof(num) ;
        printf("size : %d\n",size_int) ;
        int loop = 0 ;
        while(num!=1)
        {
            if(num%2)
                num = (3*num) + 1 ;
            else 
                num = num/2 ;
            printf("num : %d\n",num) ;
            sprintf(ptr,"%d",num) ;
            ptr+=size_int ;
            loop++ ;
        }
        sprintf(ptr,"%d",terminating_num) ;
        ptr+=size_int ;
        // printf(" haha %d\n",loop) ;
        exit(0) ;
    }
    else
    {
        wait(NULL) ;
        while(1)
        {
            int num = atoi(ptr) ;
            if(num == terminating_num)
                break ;
            printf(" %d ",num) ;
            ptr+=sizeof(num) ;
        }
        printf("\n");
    }
    return 0;
    

}