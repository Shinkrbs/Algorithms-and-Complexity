#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void init_rand(int* array, int size);
void insertion(int* array, int size);
void print_array(int* array, int size);

int main()
{
    int* array = (int*)malloc(sizeof(int) * 10);
    init_rand(array, 10);
    print_array(array, 10);
    insertion(array, 10);
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

void insertion(int* array, int size)
{
     // Starting from the second element
    for (int i = 1; i < size; i++) 
    {
        int key = array[i];
        int j = i - 1;

        // Move elements of arr[0..i-1], that are
          // greater than key, to one position to
          // the right of their current position
        while (j >= 0 && array[j] > key) 
        {
            array[j + 1] = array[j];
            j = j - 1;
        }

        // Move the key to its correct position
        array[j + 1] = key;
        print_array(array, size);
    }
}