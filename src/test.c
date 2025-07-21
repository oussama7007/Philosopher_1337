#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int     find(int *list, int size)
{
    int i = -1, count = 0;
    while(++i < size)
    {
        if(count < list[i])
            count = list[i];
    }
    i = 0;
    while(i < size)
    {
        if(count > list[i])
            count = list[i];
        i++;
    }
    i =  0;
    count++;
    while(i < size)
    {
        if(i == size -1)
        {
            count++;
        }
        if(count == list[i])
            return count ;
        i++;
    }
}
int main()
{
    int n;
    scanf("%d", &n);
    int *list = malloc(sizeof(int)* n);
    for (int i = 0; i < n; i++) {
        int num;
        scanf("%d", &num);
        list[i] = num ;
    }    
    printf("%d", find(list, n));
}