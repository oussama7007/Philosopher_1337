/// for my defending that sem_* (named semaphores) → TSan often doesn’t treat them as synchronization; expect false positives.

// pthread_mutex_* → TSan does understand them, but only if you compile & link correctly 
// (use -pthread and -fsanitize=thread together). Otherwise TSan may miss the locking/unlocking and report a race.



#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>




//long long counter = 0;



typedef struct s_data
{
    pthread_mutex_t lock;
    //sem_t *lock;
    long long counter;
}t_data;


void *philo_routine(void *arg)
{
    t_data  *data = (t_data *)arg;
    
    for (int i = 0; i < 32100; i++)
    {
       //sem_wait(data->lock);
        pthread_mutex_lock(&data->lock);
        data->counter++;
       pthread_mutex_unlock(&data->lock);
        //sem_post(data->lock);
    }
    
    return NULL;
}
int main()
{
    pthread_t t1, t2;
    t_data data;
    data.counter = 0;

    pthread_mutex_init(&data.lock, NULL);
//    data.lock = sem_open("/mysem", O_CREAT, 0644, 1);
//      if(data.lock == SEM_FAILED)
//     {
//          printf("sem_open error ");
//          return 1;
//     }
    pthread_create(&t1, NULL, philo_routine, &data);
    pthread_create(&t2, NULL, philo_routine, &data);

    long long a = 32100 * 2;
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("[%lld] what it should be\n", a);
    printf("[%lld] the result\n", data.counter);

    //sem_close(data.lock);
    //sem_unlink("/mysem");
}

// #include <pthread.h>
// #include <unistd.h>
// #include <semaphore.h>
// #include <fcntl.h>
// #include <stdio.h>
// #include <stdlib.h>

// typedef struct s_data
// {
//     sem_t *lock;
//     long long a;
// }t_data;

// void *philo_routine(void *arg)
// {
//     t_data *data = (t_data *)arg;
//     for(int i = 0; i < 321000; i++)
//     {
//         sem_wait(data->lock);
//         data->a++;
//         sem_post(data->lock);
//     }
//     return NULL;
// }

// int main()
// {
//     t_data data;
//     data.a = 0;
//     pthread_t t1, t2;
//     data.lock = sem_open("/mysem", O_CREAT, 0644, 1);
//     if(data.lock == SEM_FAILED)
//     {
//         printf("semaphore failed to open cus of it's already exist\n");
        
//         sem_unlink("/mysem");
//         exit(1);
//     }
//     if(pthread_create(&t1, NULL, philo_routine, &data) != 0)
//     {
//         sem_close(data.lock);
//         sem_unlink("/mysem");
//         exit(0);
//     } 
//     if(pthread_create(&t2, NULL, philo_routine, &data))
//     {
//         sem_close(data.lock);
//         sem_unlink("/mysem");
//         pthread_join(t1, NULL);
//         exit(0);
//     }
//     pthread_join(t1, NULL);
//     pthread_join(t2, NULL);
//     long long b = 321000*2;
//     printf("the expected res is [%lld]\n", b);
//     printf("the res is          [%lld]\n", data.a);
//     sem_close(data.lock);
//     sem_unlink("/mysem");
// }