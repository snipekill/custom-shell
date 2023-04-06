#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    // printf("%s",argv[1]) ;
    struct timeval current_time;
    pid_t child = fork();
    const int SIZE = 4096;
    const char *name = "OS";
    int fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    char *ptr = (char *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (child < 0)
    {
        printf("error in creating the child process");
    }
    else if (child == 0)
    {
        printf("inside child process\n");
        gettimeofday(&current_time, NULL);
        // printf("Current Time : %ld\n",start.tv_usec) ;
        sprintf(ptr, "%ld\n", current_time.tv_usec);
        argv++;
        execvp(argv[0], argv);
        exit(0);
    }
    else if (child > 0)
    {
        wait(NULL);
        gettimeofday(&current_time, NULL);
        // printf("Current Time : %ld\n",end.tv_usec) ;
        // printf("%s\n",ptr) ;
        long int start = atol(ptr);
        printf("\n\nExecution Time in Milliseconds : %lf\n", (double)(current_time.tv_usec - start) / 1000);
    }

    return 0;
}