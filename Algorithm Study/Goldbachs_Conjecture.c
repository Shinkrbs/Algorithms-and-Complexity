#include <stdio.h>

int isPrime(int x) 
{
    if (x < 2) return 0;
    for (int i = 2; i*i <= x; i++) 
    {
        if (x % i == 0) 
            return 0;
    }
    return 1;
}

int main() 
{
    int cur = 50;
    for (int i = 3; i < cur; i += 2)
    {
        if (isPrime(i))
        {
            for (int j = 3; j < cur; j += 2)
            {
                if (isPrime(j) && i + j == cur)
                    printf("%d + %d = %d\n", i, j, cur);
            }
        }
    }
    return 0;
}
