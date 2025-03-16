#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void init_rand(int* array, int size);
void selection(int* array, int size);
void print_array(int* array, int size);

int main()
{
    int* array = (int*)malloc(sizeof(int) * 10);
    init_rand(array, 10);
    print_array(array, 10);
    selection(array, 10);
    //print_array(array, 10);
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

void selection(int* array, int size)
{
    for (int i = 0; i < size - 1; i++) 
    {
        // Assume the current position holds
        // the minimum element
        int min_idx = i;
        
        // Iterate through the unsorted portion
        // to find the actual minimum
        for (int j = i + 1; j < size; j++) 
        {
            if (array[j] < array[min_idx]) 
            {
                // Update min_idx if a smaller element is found
                min_idx = j;
            }
        }  
        // Move minimum element to its
        // correct position
        int temp = array[i];
        array[i] = array[min_idx];
        array[min_idx] = temp;

        print_array(array, size);
    }
}