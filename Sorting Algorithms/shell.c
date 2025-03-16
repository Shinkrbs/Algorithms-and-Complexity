#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void init_rand(int* array, int size);
void shell(int* array, int size);
void print_array(int* array, int size);

int main()
{
    int* array = (int*)malloc(sizeof(int) * 10);
    init_rand(array, 10);
    print_array(array, 10);
    shell(array, 10);
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

void shell(int* array, int size)
{
    // Start with a big gap, then reduce the gap
    for (int gap = size / 2; gap > 0; gap /= 2)
    {
        printf("\nGap: %d\n", gap);
        // Do a gapped insertion sort for this gap size.
        // The first gap elements a[0..gap-1] are already in gapped order
        // keep adding one more element until the entire array is
        // gap sorted 
        for (int i = gap; i < size; i += 1)
        {
            // add a[i] to the elements that have been gap sorted
            // save a[i] in temp and make a hole at position i
            int temp = array[i];

            // shift earlier gap-sorted elements up until the correct 
            // location for a[i] is found
            int j;            
            for (j = i; j >= gap && array[j - gap] > temp; j -= gap)
                array[j] = array[j - gap];
            
            //  put temp (the original a[i]) in its correct location
            array[j] = temp;
            print_array(array, size);
        }
    }
}