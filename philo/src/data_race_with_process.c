#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>


int main()
{
        FILE *f = fopen("log.txt", "w");
        fclose(f);
        sem_t *sem = sem_open("/me", O_CREAT | O_EXCL , 0644, 1);
        if(sem == SEM_FAILED)
        {
                perror("Error");
                exit(1);
        }
        for(int i = 0; i < 7; i++)
        {
                pid_t pid = fork();
                if(pid == 0)
                {
                        sem_wait(sem);
                        FILE *f = fopen("log.txt", "a");
                        for(int j = 0; j < 7; j++)
                        {
                                fprintf(f,"Child [%d] process --- line %d\n", getpid(), j + 1);
                        }
                        fclose(f);
                        sem_post(sem);
                        exit(0);
                }
        }
        for(int N = 0;  N < 7; N++)
                wait(NULL);
        sem_close(sem);
       sem_unlink("/me");
}