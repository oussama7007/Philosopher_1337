#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
#include <unistd.h>

void        *function(void * args)
{
    int *i = (int *)args;
    sleep (1);
    printf("i did reached thread-%d\n", *i);
    return NULL;
}

int main()
{
    pthread_t t1, t2;

    int a = 0;
    int b = 1;
    pthread_create(&t1, NULL, function, (void *)&a);
    pthread_create(&t2, NULL, function, (void *)&b);
    sleep (3);
    printf("\n ila jab\n");
    while (is_die)
    return 0;

}



