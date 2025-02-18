#include <iostream>
#include <chrono>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <iomanip>

std::vector<int> rand_data();
void rec_to_text(std::string file_name, std::vector<double> &result);

//n^2 algorithms
void selectionSort(); // Done
void bubbleSort(); // Done
void insertionSort(); // Done

//O(n logn) algorithms
void mergeSort(std::vector<int> &a, int start, int end, std::vector<double> &result); // Done
void mergeArr(std::vector<int> &a,int start, int mid, int end); // Done
void quickSort(std::vector<int> &a,int start, int end, std::vector<double> &result);

int main()
{
    selectionSort();
    bubbleSort();
    insertionSort();

    // Merge Sort
    std::vector<int> data_merge = rand_data();
    std::vector<double> result_merge;

    mergeSort(data_merge, 0, data_merge.size(), result_merge);
    rec_to_text("Merge.txt", result_merge);

    // Quick Sort
    std::vector<int> data_quick = rand_data();
    std::vector<double> result_quick;

    quickSort(data_quick, 0, data_quick.size(), result_quick);
    rec_to_text("Quick.txt", result_quick);


    return 0;
}

std::vector<int> rand_data()
{
    int size = 1000;
    std::vector<int> data;
    std::srand (std::time(NULL));

    for (int i = 0; i < size; i++)
        data.push_back(100 + rand() % 100000);
    return data;
}

void rec_to_text(std::string file_name, std::vector<double> &result)
{
    std::ofstream file(file_name);

    if (!file)
    {
        std::cout << "Error: Unable to Open File." << std::endl;
        return;
    }
    file << std::fixed << std::setprecision(10); 
    for (const auto &results : result)
        file << results << "\n";

    std::cout << "Program Done!";
    file.close();
}

void selectionSort()
{
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> data = rand_data();
    std::vector<double> result;
    int small, idx_small;

    for(int i = 0; i < data.size() - 1; i++)
    {
        idx_small = i;
        for(int j = i + 1; j < data.size(); j++)
        {
            if(data[j] < data[idx_small])
                idx_small = j;
        }
    std::swap(data[i], data[idx_small]);

    // Calculating time
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_taken = end - start;
    result.push_back(time_taken.count());

    for (int idx = 0; idx < data.size(); idx++)
        std::cout << data[idx] << ",";
    std::cout << std::endl;
    }

    // Saving to Text File
    rec_to_text("Selection.txt", result);
}

void bubbleSort()
{
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> data = rand_data();
    std::vector<double> result;
    int i = 0;
    bool swp = 1;

    while(swp)
    {
        swp = 0;
        for (int j = data.size() - 1; j > i; j--)
        {
            if (data[j] < data[j - 1])
            {
                std::swap(data[j], data[j - 1]);
                swp = 1;
            }
        }

        for (int idx = 0; idx < data.size();idx++)
            std::cout << data[idx] <<",";
        std::cout << std::endl;
        i++;

        // Calculating time
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_taken = end - start;
        result.push_back(time_taken.count());
    }
    
    // Saving to Text File
    rec_to_text("Bubble.txt", result);
}

void insertionSort()
{
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> data = rand_data();
    std::vector<double> result;
    int key,j;

    for (int i = 0; i < data.size(); i++)
    {
        key = data[i];
        j = i - 1;
        while(key < data[j] && j >= 0)
        {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = key;

        for (int idx = 0; idx < data.size(); idx++)
            std::cout << data[idx] << ",";
        std::cout << std::endl;

        // Calculating time
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_taken = end - start;
        result.push_back(time_taken.count());
    }

    // Saving to Text File
    rec_to_text("Insertion.txt", result);
}

void mergeSort(std::vector<int> &a, int start, int end, std::vector<double> &result)
{
    auto s = std::chrono::high_resolution_clock::now();
    int mid;
    if(start < end)
    {
        mid = (start + end) / 2;
        //cout<<start<<","<<mid<<",";

        mergeSort(a, start, mid, result);
        mergeSort(a, mid + 1, end, result);

        for(int idx = 0; idx < 10; idx++)
            std::cout << a[idx] << ",";
        std::cout<<std::endl;
        mergeArr(a, start, mid, end);

        for (int idx = 0; idx < 10; idx++)
            std::cout << a[idx] << ",";
        std::cout << std::endl;

        auto e = std::chrono::high_resolution_clock::now(); 
        std::chrono::duration<double> time_taken = e - s;
        result.push_back(time_taken.count()); 
    }
}

void mergeArr(std::vector<int> &a,int start, int mid, int end)
{
    int size = end - start + 1; 
    std::vector<int> temp(size);

    int ptr1 = start, ptr2 = mid + 1, j = 0;

    /* The while loop below would execute  equal to the
        minimum of mid and (n-mid)
    */
    while (ptr1 <= mid && ptr2 <= end)
    {
        if (a[ptr1] < a[ptr2])
            temp[j++] = a[ptr1++];
        else
            temp[j++] = a[ptr2++];
    }

    while (ptr1 <= mid)
        temp[j++] = a[ptr1++];

    while (ptr2 <= end)
        temp[j++] = a[ptr2++];

    for (int i = 0; i < size; i++)
        a[start + i] = temp[i];
}

void quickSort(std::vector<int> &a, int start, int end, std::vector<double> &result)
{
    if (start >= end)
        return;

    auto s = std::chrono::high_resolution_clock::now();

    // Choose the last element as pivot
    int pivot = a[end];
    int i = start - 1;

    for (int j = start; j < end; j++)
    {
        if (a[j] <= pivot)
        {
            i++;
            std::swap(a[i], a[j]);
        }
    }
    std::swap(a[i + 1], a[end]);

    int partitionIdx = i + 1;

    auto e = std::chrono::high_resolution_clock::now(); 
    std::chrono::duration<double> time_taken = e - s;
    result.push_back(time_taken.count());

    quickSort(a, start, partitionIdx - 1, result);
    quickSort(a, partitionIdx + 1, end, result);

    // Print the array after each partition step for debugging
    for (int idx = 0; idx < a.size(); idx++)
        std::cout << a[idx] << ",";
    std::cout << std::endl;
}
