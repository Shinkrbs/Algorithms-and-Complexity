#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void init_rand(int* array, int size);
void bubble(int* array, int size);
void print_array(int* array, int size);

int main()
{
    int* array = (int*)malloc(sizeof(int) * 10);
    init_rand(array, 10);
    print_array(array, 10);
    bubble(array, 10);
    print_array(array, 10);
}

void init_rand(int* array, int size)
{
    srand(time(0));
    for(int i = 0; i < size; i++)
        array[i] = rand() % 100;
    return;
}

void print_array(int* array, int size)
{
    for(int i = 0; i < size; i++)
        printf("%d ", array[i]);
    printf("\n");
    return;
}

void bubble(int* array, int size)
{
    int flag = 0;
    for(int i = 0; i < size - 1; i++)
    {
        for(int j = 0; j < size - i - 1; j++)
        {
            flag = 0;
            if(array[j] > array[j + 1])
            {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                flag = 1;
            }
            print_array(array, size);
        }
        if(!flag)
            break;
    }
    return;
}