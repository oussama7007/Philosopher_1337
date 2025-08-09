#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    sem_t *semA = sem_open("/semA", O_CREAT | O_EXCL, 0644, 1);
    sem_t *semB = sem_open("/semB", O_CREAT | O_EXCL, 0644, 1);

    if (semA == SEM_FAILED || semB == SEM_FAILED) {
        perror("sem_open");
        // Try to unlink and reopen if they already exist
        sem_unlink("/semA");
        sem_unlink("/semB");
        semA = sem_open("/semA", O_CREAT, 0644, 1);
        semB = sem_open("/semB", O_CREAT, 0644, 1);
        if (semA == SEM_FAILED || semB == SEM_FAILED) {
            perror("sem_open retry");
            exit(EXIT_FAILURE);
        }
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process: locks semA then semB
        printf("Child: waiting for semA\n");
        sem_wait(semA);
        //  sem_wait(semB); // to fix deadlock
        printf("Child: locked semA\n");
        sleep(1);  // simulate some work

        printf("Child: waiting for semB\n");
        sem_wait(semB);  // Deadlock can happen here
        // sem_wait(semA); // to fix deadlock 
        printf("Child: locked semB\n");

        // Release semaphores
        sem_post(semB);
        sem_post(semA);

        sem_close(semA);
        sem_close(semB);

        exit(0);
    } else {
        // Parent process: locks semB then semA
        printf("Parent: waiting for semB\n");
        sem_wait(semB);
        printf("Parent: locked semB\n");
        sleep(1);  // simulate some work

        printf("Parent: waiting for semA\n");
        sem_wait(semA);  // Deadlock can happen here
        printf("Parent: locked semA\n");

        // Release semaphores
        sem_post(semA);
        sem_post(semB);

        sem_close(semA);
        sem_close(semB);

        wait(NULL);

        sem_unlink("/semA");
        sem_unlink("/semB");
    }

    return 0;
}
