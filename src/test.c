#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
#include <unistd.h>
/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

void    *function(void *arg)
{   
    long sum = 0;
    long *add_number = (long * )(arg);
    for (long i = 0; i < 1000000000; i++)
        sum += *add_number;
    printf("Add number = %ld\n", *add_number);
    return NULL;
}
long long gt_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
int main()
{
    // pthread_t thread1 , thread2;
    // long long value = 8;
    // long long value2 = 20;
    // pthread_create(&thread1, NULL, function, &value);
    // pthread_create(&thread2, NULL, function, &value2);
   
    
    
    while (true)
    {
        long long time  = gt_time();
        usleep(1000);
        long long value = gt_time() - time + 0.01;
        if(value != 0)
            printf("error and value = %lld \n", value);
        else 
            printf("correct\n");
    }
    // pthread_join(thread1, NULL);
    // pthread_join(thread2, NULL);

    // pthread_mutex_t lock;
    // pthread_mutex_init(&lock, NULL);
    // pthread_mutex_lock(&lock);
    // printf("%d", 5555);
}




