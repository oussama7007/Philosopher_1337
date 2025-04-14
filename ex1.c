#include <stdio.h>
#include <pthread.h>
#include <string.h>


typedef struct  s_data
{
    int buffer[5];
    pthread_mutex_t lock;
} t_data;

void *handle_thread(void *av)
{
    t_data *data = (t_data *)av;
    int i = 0;
   
    while(i < 5)
    {
        pthread_mutex_lock(&data->lock);
        data->buffer[i] = i;
        pthread_mutex_unlock(&data->lock);
        i++;
    }
    return NULL;
}
int main()
{
    t_data data;
    memset(&data, 0,sizeof(data));
    pthread_t t1, t2;
    pthread_mutex_init(&data.lock, NULL);
    pthread_create(&t1, NULL, handle_thread, &data);
    pthread_create(&t2, NULL, handle_thread, &data);

    pthread_join(&t1, NULL);
    pthread_join(&t2, NULL);

    pthread_mutex_destroy(&data.lock);
    
    
}