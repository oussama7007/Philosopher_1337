# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

int i = 0;
void *routine(void *arg)
{
    int j = 0;
    while (j < 2000000)
{
    j++;
    i++;
}
    return(NULL);
}

int main()
{
   
}