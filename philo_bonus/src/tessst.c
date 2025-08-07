#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <semaphore.h>

#define SEM_A "/sem_a"
#define SEM_B "/sem_b"

void process1()
{
    sem_t *semA = sem_open(SEM_A, 0);
    sem_t *semB = sem_open(SEM_B, 0);

    printf("P1: Locking A...\n");
    sem_wait(semA);
    printf("P1: A locked. Sleeping...\n");
    sleep(1);

    printf("P1: Locking B...\n");
    sem_wait(semB); // 💥 DEADLOCK here if P2 already holds B
    printf("P1: B locked!\n");

    sem_post(semA);
    sem_post(semB);
    printf("P1: Done.\n");

    sem_close(semA);
    sem_close(semB);
    exit(0);
}

void process2()
{
    sem_t *semA = sem_open(SEM_A, 0);
    sem_t *semB = sem_open(SEM_B, 0);

    printf("P2: Locking B...\n");
    sem_wait(semA);
    printf("P2: B locked. Sleeping...\n");
    sleep(1);

    printf("P2: Locking A...\n");
    sem_wait(semB); // 💥 DEADLOCK here if P1 already holds A
    printf("P2: A locked!\n");

    sem_post(semB);
    sem_post(semA);
    printf("P2: Done.\n");

    sem_close(semA);
    sem_close(semB);
    exit(0);
}

int main()
{
    sem_unlink("/sem_a");
    sem_unlink("/sem_b");
    // Create both semaphores with value 1
    sem_t *semA = sem_open(SEM_A, O_CREAT | O_EXCL, 0644, 1);
    sem_t *semB = sem_open(SEM_B, O_CREAT | O_EXCL, 0644, 1);

    if (semA == SEM_FAILED || semB == SEM_FAILED)
    {
        perror("sem_open");
        sem_unlink(SEM_A);
        sem_unlink(SEM_B);
        exit(1);
    }

    pid_t pid1 = fork();
    if (pid1 == 0)
        process1();

    pid_t pid2 = fork();
    if (pid2 == 0)
        process2();

    // Wait for both children (they will never finish due to deadlock)
    wait(NULL);
    wait(NULL);

    // Cleanup
    sem_close(semA);
    sem_close(semB);
    sem_unlink(SEM_A);
    sem_unlink(SEM_B);

    return 0;
}

