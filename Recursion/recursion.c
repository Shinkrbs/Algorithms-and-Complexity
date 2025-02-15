#include <stdio.h>

int factorial(int n);

int main()
{
    printf("%d", factorial(3));
    return 0;
}

int factorial(int n)
{
    if(n == 1) return 1;
    // printf("%d * %d\n", n, n - 1);
    return n * factorial(n - 1);
}