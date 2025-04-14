#include <stdio.h>
#include <pthread.h>


typedef struct {
    int counter;
    pthread_mutex_t lock;
} data;

void *thread_routine(void *av)
{
    data *da =(data *)av; 
    int i = 0;
    while(i < 1000000)
    {
        pthread_mutex_lock(&da->lock);
        da->counter++;
        pthread_mutex_unlock(&da->lock);
        i++;
    }

    
    return NULL;
}

int main()
{
    pthread_t t1, t2, t3, t4, t5, t6, t7;
    data da;
    da.counter = 0; 
    pthread_mutex_init(&da.lock, NULL);

    pthread_create(&t1, NULL, thread_routine, &da);
    pthread_create(&t2, NULL, thread_routine, &da);
    pthread_create(&t3, NULL, thread_routine, &da);
    pthread_create(&t4, NULL, thread_routine, &da);
    pthread_create(&t5, NULL, thread_routine, &da);
    pthread_create(&t6, NULL, thread_routine, &da);
    pthread_create(&t7, NULL, thread_routine, &da);
  
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    pthread_join(t5, NULL);
    pthread_join(t6, NULL);
    pthread_join(t7, NULL);

    printf("final counter :%d\n", da.counter);
    pthread_mutex_destroy(&da.lock);
    return 0;
}