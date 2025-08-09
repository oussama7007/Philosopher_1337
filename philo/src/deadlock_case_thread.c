#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>





pthread_mutex_t lock1;
pthread_mutex_t lock2;



void    *philo_routine(void *arg)
{
        pthread_mutex_lock(&lock1);
        // pthread_mutex_lock(&lock2); // deadlock case 
        printf("On philo [1] --lock <1>\n");
        sleep(1);

        pthread_mutex_lock(&lock2);
        //pthread_mutex_lock(&lock1);// deadlock case
        printf("On philo [1] --lock <2>\n");

        pthread_mutex_unlock(&lock2);
        pthread_mutex_unlock(&lock1);
        return NULL;
}
void *philo_routine2(void *arg)
{
        pthread_mutex_lock(&lock1);
        printf("On philo [2] --lock <1>\n");

        sleep(1);
        pthread_mutex_lock(&lock2);
        printf("On philo [2] --lock <2>\n");

        pthread_mutex_unlock(&lock1);
        pthread_mutex_unlock(&lock2);
        return NULL;
}


int main()
{
    pthread_t t1, t2;

    pthread_mutex_init(&lock1, NULL);
    pthread_mutex_init(&lock2, NULL);

    pthread_create(&t1, NULL, philo_routine, NULL);
    pthread_create(&t2, NULL, philo_routine2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
}


