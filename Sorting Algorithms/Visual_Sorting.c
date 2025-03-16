#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define UP 72
#define DOWN 80
#define ENTER 13

// N^2 sorting algorithms
void bubble(int* array, int size);
void selection(int* array, int size);
void insertion(int* array, int size);
void shell(int* array, int size);
int quick_select(int* array, int start, int end , int IthIdx);
int partition(int* array, int start, int end);

// N(log(N)) sorting algorithms
// Merge Sort
void merge_Arr(int* array, int start, int mid, int end);
void merge(int* array, int start, int end);
void quick(int* array, int start, int end);

void print_array(int* array, int size);
void swap(int* a, int* b);

// Debugging
void rand_int(int* array, int size);

void cmd();
void display_menu(int selection);
int* get_info(int* size);

int main()
{
    // int size = 10;
    // int* array = (int*)malloc(sizeof(int) * size);

    // rand_int(array, size);
    // print_array(array, size);

    //bubble(array, size);
    //selection(array, size);
    //insertion(array, size);
    //shell(array, size);

    // int k = 0;
    // int kth_smallest = quick_select(array, 0, size - 1, k);
    // printf("The %d smallest element is: %d\n", k + 1, kth_smallest);

    //merge(array, 0, size - 1);
    //quick(array, 0, size - 1);
    //print_array(array, size);

    cmd();
    return 0;
}

void rand_int(int* array, int size)
{
    srand(time(0));
    for(int i = 0; i < size; i++)
        array[i] = rand() % 30; // produce numbers 1 -> 15
}

void print_array(int* array, int size)
{
    for(int i =0; i < size; i++)
        printf("%d ", array[i]);
    printf("\n\n");
}

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubble(int* array, int size)
{
    int i = 0;
    bool swp = 1;
    int step = 1;

    while(swp)
    {
        swp = 0;
        printf("Step %d: ", step++); 
        print_array(array, size); 

        for(int j = size - 1; j > i; j--)
        {
            if(array[j] < array[j - 1])
            {
                printf("Swapping %d and %d\n", array[j - 1], array[j]);
                swap(&array[j], &array[j - 1]);
                swp = 1;
                //print_array(array, size);
            }
        }
        i++;
    }
}

void selection(int* array, int size)
{
    int idx_small, ctr = 1;

    for(int i = 0; i < size - 1; i++)
    {
        idx_small = i;
        for(int j = i + 1; j < size; j++)
        {
            if(array[j] < array[idx_small])
                idx_small = j;
        }

        printf("Swapping %d and %d\n", array[i], array[idx_small]);
        swap(&array[i], &array[idx_small]); 

        printf("Step %d: ", ctr);
        print_array(array, size);
        ctr++;
    }
}

void insertion(int* array, int size)
{
    int key, j;
    for(int i = 1; i < size; i++)
    {
        key = array[i];
        j = i - 1;

        printf("Inserting %d: ", key);

        while(key < array[j] && j >= 0)
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;

        printf("Step %d: ", i);
        print_array(array, size);
    }
}

void shell(int* array, int size)
{
    int i, j, d;
    int tmp, ctr = 1;

    for(d = size / 2; d > 0; d /= 2)
    {
        printf("Gap %d:\n", d);

        for(i = d; i < size; i++)
        {
            tmp = array[i];
            for(j = i; j > d - 1; j -= d)
            {
                if(tmp < array[j - d])
                    array[j] = array[j - d];
                else
                    break;
            }
            array[j] = tmp;
        }
        printf("Step %d: ", ctr);
        print_array(array, size);
        ctr++;
    }
}

void merge_Arr(int* array, int start, int mid, int end)
{
    int size = end - start + 1;
    int* temp = (int*)malloc(sizeof(int) * size);
    int ptr1 = start, ptr2 = mid + 1, j = 0;

    /* The while loop below woud execute equal to the minimun
    of mid  and (n - mid)*/

    while(ptr1 <= mid && ptr2 <= end)
    {
        if(array[ptr1] < array[ptr2])
        {
            temp[j] = array[ptr1];
            ptr1++;
            j++;
        }
        else
        {
            temp[j] = array[ptr2];
            ptr2++;
            j++;
        }
    }

    while (ptr1 <= mid)
    {
        temp[j] = array[ptr1];
        ptr1++;
        j++;
    }

    while (ptr2 <= end)
    {
        temp[j] = array[ptr2];
        ptr2++;
        j++;
    }
    // if(ptr1 < mid + 1)
    // {
    //     for(i = j; i < size + 1; i++)
    //     {
    //         temp[i] = array[ptr1];
    //         ptr1++;
    //     }
    // }

    // if(ptr2 < end + 1)
    // {
    //     for(int i = j; i < size + 1; i++)
    //     {
    //         temp[i] = array[ptr2];
    //         ptr2++;
    //     }
    // }

    for(int i = 0; i < size; i++)
        array[start + i] = temp[i];
}

void merge(int* array, int start, int end)
{
    static int step = 1;  
    if(start < end)
    {
        int mid = (start + end) / 2;
        
        merge(array, start, mid);
        merge(array, mid + 1, end);
        
        printf("Merging Step %d: Merging array[%d:%d]" 
            "and array[%d:%d]\n", step++, start, mid, mid + 1, end);
        
        merge_Arr(array, start, mid, end);
        
        printf("After Merging Step %d: ", step - 1);
        print_array(array + start, end - start + 1);
    }
}

void quick(int* array, int start, int end)
{
    static int step = 1;
    int i, j, pivot;
    if(start < end)
    {
        pivot = array[start];
        i =  start + 1;
        j = end;
        
        printf("Step %d: Choosing pivot %d at index %d\n", step++, pivot, start);
        printf("Before partitioning: ");
        print_array(array + start, end - start + 1);

        while(array[i] < pivot)
            i++;
        while(array[j] > pivot)
            j--;
        
        while(i < j)
        {
            swap(&array[i], &array[j]);
            i++;
            
            while(array[i] < pivot)
                i++;
            j--;
            while(array[j] > pivot)
                j--;
        }
        swap(&array[start], &array[j]);

        printf("After partitioning: ");
        print_array(array + start, end - start + 1);
        printf("Pivot %d placed at index %d\n\n", array[j], j);

        quick(array, start, j - 1);
        quick(array, j + 1, end);
    }
}

int quick_select(int* array, int start, int end , int IthIdx)
{
    int q, k, i;
    
    if(start == end)
        return (array[start]);

    printf("Selecting %d-th smallest element in range [%d:%d]\n", IthIdx + 1, start, end);

    q = partition(array, start, end);
    printf("Partitioned around index %d, pivot = %d\n", q, array[q]);
    print_array(array, end - start + 1);

    k = q - start + 1;
    if(IthIdx < k)
    {
        printf("Recursing into left partition [%d:%d]\n", start, q - 1);
        if((q - 1) == -1)
            printf("End = -1. STOP\n");
        return (quick_select(array, start, q, IthIdx));
    }
    else
    {
        printf("Recursing into right partition [%d:%d]\n", q + 1, end);
        return (quick_select(array, q + 1, end, IthIdx - k));
    }
}

int partition(int* array, int start, int end)
{
    int pivot = array[start];
    int i = start + 1, j = end;

    printf("Partitioning with pivot %d at index %d\n", pivot, start);
    print_array(array + start, end - start + 1);

    while(array[i] < pivot)
        i++;
    while(array[j] > pivot)
        j--;
    
    while(i < j)
    {
        printf("Swapping %d and %d\n", array[i], array[j]);
        swap(&array[i], &array[j]);
        i++;
        
        while(array[i] < pivot)
            i++;
        j--;
        while(array[j] > pivot)
            j--;
    }
    swap(&array[start], &array[j]);
    printf("Pivot placed at index %d\n", j);
    return j;
}

void cmd()
{
    int* array = NULL;
    int selected = 0, key, size;

    while(1)
    {
        display_menu(selected);
        key = getch();

        if(key == UP && selected > 0)
            selected--;
        else if(key == DOWN && selected < 7)
            selected++;
        else if(key == ENTER)
        {
            system("cls");

            if (selected == 7) 
            {
                printf("Program Stopped\n");
                return;
            }

            array = get_info(&size);
            switch(selected)
            {
                case 0:
                    system("cls");
                    selection(array, size);
                    break;
                case 1:
                    system("cls");
                    bubble(array, size);
                    break;
                case 2:
                    system("cls");
                    insertion(array, size);
                    break;
                case 3:
                    system("cls");
                    shell(array, size);
                    break;
                case 4:
                    system("cls");
                    merge(array, 0, size - 1);
                    break;
                case 5:
                    system("cls");
                    quick(array, 0, size - 1);
                    break;
                case 6:
                    system("cls");
                    int k = 0;
                    int kth_smallest = quick_select(array, 0, size - 1, k);
                    printf("The %d smallest element is: %d\n", k + 1, kth_smallest);
                    break;
            }
            printf("Sorted Array: ");
            print_array(array, size);

            free(array);

            printf("Press any key to return to menu...");
            getch();
        }
    }
}

void display_menu(int selected)
{
    system("cls");
    printf("Visualize Sorting Steps\n\n");
    char* options[] = {"Selection Sort", "Bubble Sort", "Insertion Sort", 
                "Shell Sort", "Merge Sort", "Quick Sort", "Quick Select", "Exit"};
    int num_options = sizeof(options) / sizeof(options[0]);

    for (int i = 0; i < num_options; i++) 
    {
        if (i == selected)
            printf(" > %s < \n", options[i]); 
        else
            printf("   %s   \n", options[i]);
    }
}

int* get_info(int* size)
{
    printf("Enter Size of Array: ");
    scanf("%d", size);

    int* array = (int*)malloc(sizeof(int) * (*size));
    printf("Enter %d Elements Separated by Spaces (ex. 1 2 3 4): ", *size);
    for(int i = 0; i < *size; i++)
        scanf("%d", &array[i]);

    return array;
}