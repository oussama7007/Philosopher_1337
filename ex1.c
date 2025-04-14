#include <stdio.h>
#include <pthread.h>



typedef struct  s_data
{
    int buffer;
    pthread_mutex_t lock;
} t_data;

void *handle_thread(void *av)
{
    t_data *data = (t_data *)av;
    

}
int main(int ac, char **av)
{
    pthread_t t1, t2;
    pthread_create(&t1, NULL, hendle_thread, NULL);
}