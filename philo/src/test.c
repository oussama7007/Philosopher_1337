# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

pthread_mutex_t lock;
long long b = 0;
long long *a = &b;

void *function(void)
{
    pthread_mutex_lock(&lock);
    for(int  i = 0 ; i < (long long){46544365}; i++)
        (*a)++;
    pthread_mutex_unlock(&lock);
    return NULL;
}


int     main()
{
    pthread_t t1, t2;
    // pthread_mutex_init(&lock, NULL);
    // pthread_create(&t1, NULL, function, &a);
    // pthread_create(&t2, NULL, function, &a);
    function();
    function();
    // pthread_join(t1, NULL);
    // pthread_join(t2, NULL);
    long long b = 46544365 * 2;
    printf("we expect %lld \n the result is %lld\n ", b,  *a);
}