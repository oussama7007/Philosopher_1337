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
    pthread_t thread, thread1, thread3;
    long value = 0;
    long value2 = 2;
    function((void *) &value);
    function((void *) &value2);
    // pthread_create(&thread,NULL, function, &value);
    // pthread_create(&thread1,NULL, function,  &value2);
    //pthread_create(&thread3,NULL, function,  &value);
    pthread_join(thread, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread3, NULL);
}