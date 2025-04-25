#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>



int main()
{
    struct timeval tv;
    if(gettimeofday(&tv, NULL) != 0)
    {
        printf("get time of day failed");
    }
    else 
    {
        printf("secodes: %ld\n", tv.tv_sec);
        printf("milisecondes: %d\n", tv.tv_usec);
    }
    return 0;
}