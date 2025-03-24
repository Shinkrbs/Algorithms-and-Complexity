#include <stdio.h>

int isPrime(int n);

int main()
{
    for(int i = 0; i <= 100; i++)
    {
        printf("%d: ", i);
        if(isPrime(i))
            printf("Prime\n");
        else
            printf("Not Prime\n");
    }
    return 0;
}

int isPrime(int n)
{
    if(n < 2)
        return 0;
    for(int i = 2; i < n / 2; i++)
    {
        if(n % i == 0)
            return 0;
    }
    return 1;
}