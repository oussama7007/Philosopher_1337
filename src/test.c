#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
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
int main()
{
    pthread_mutex_t lock;
    pthread_mutex_init(&lock, NULL);
    pthread_mutex_lock(&lock);
    printf("%d", 5555);
int ret1 = pthread_mutex_unlock(&lock);
printf("\nret1 = %d (%s)\n", ret1, strerror(ret1));

int ret2 = pthread_mutex_unlock(&lock);
printf("ret2 = %d (%s)\n", ret2, strerror(ret2));

int ret3 = pthread_mutex_unlock(&lock);
printf("ret3 = %d (%s)\n", ret3, strerror(ret3));
}