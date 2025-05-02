

#include <stdio.h>


long long fu(void)
{
    return 1234567897;
}

int main()
{
    int a = fu();
    long long  b = 4;
    short int c = fu() + b + a;
    printf("%d\n\n", c);
    printf("c :%zu\n\n", sizeof(c));
    printf("b :%zu\n\n", sizeof(b));
    printf("a :%zu\n\n", sizeof(a));
}