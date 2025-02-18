#include <iostream>
#include <chrono>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <iomanip>

std::vector<int> rand_data(int size);
void rec_to_text(std::string file_name, std::vector<double> &result);

// Sorting algorithms
void selectionSort(std::vector<int> &data);
void bubbleSort(std::vector<int> &data);
void insertionSort(std::vector<int> &data);
void mergeSort(std::vector<int> &a, int start, int end);
void mergeArr(std::vector<int> &a, int start, int mid, int end);
void quickSort(std::vector<int> &a, int start, int end);

int main() {
    // Array sizes to test
    std::vector<int> sizes = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
    
    // Create files for results
    std::vector<double> result_selection, result_bubble, result_insertion, result_merge, result_quick;

    for (int size : sizes) {
        std::vector<int> data = rand_data(size);

        // Measure execution time for Selection Sort
        auto start = std::chrono::high_resolution_clock::now();
        selectionSort(data);
        auto end = std::chrono::high_resolution_clock::now();
        result_selection.push_back(std::chrono::duration<double, std::milli>(end - start).count());

        // Measure execution time for Bubble Sort
        data = rand_data(size);  // Reset data
        start = std::chrono::high_resolution_clock::now();
        bubbleSort(data);
        end = std::chrono::high_resolution_clock::now();
        result_bubble.push_back(std::chrono::duration<double, std::milli>(end - start).count());

        // Measure execution time for Insertion Sort
        data = rand_data(size);  // Reset data
        start = std::chrono::high_resolution_clock::now();
        insertionSort(data);
        end = std::chrono::high_resolution_clock::now();
        result_insertion.push_back(std::chrono::duration<double, std::milli>(end - start).count());

        // Measure execution time for Merge Sort
        data = rand_data(size);  // Reset data
        start = std::chrono::high_resolution_clock::now();
        mergeSort(data, 0, data.size() - 1);
        end = std::chrono::high_resolution_clock::now();
        result_merge.push_back(std::chrono::duration<double, std::milli>(end - start).count());

        // Measure execution time for Quick Sort
        data = rand_data(size);  // Reset data
        start = std::chrono::high_resolution_clock::now();
        quickSort(data, 0, data.size() - 1);
        end = std::chrono::high_resolution_clock::now();
        result_quick.push_back(std::chrono::duration<double, std::milli>(end - start).count());
    }

    // Write results to text files
    rec_to_text("SelectionSortTimes.txt", result_selection);
    rec_to_text("BubbleSortTimes.txt", result_bubble);
    rec_to_text("InsertionSortTimes.txt", result_insertion);
    rec_to_text("MergeSortTimes.txt", result_merge);
    rec_to_text("QuickSortTimes.txt", result_quick);

    return 0;
}

std::vector<int> rand_data(int size) 
{
    std::vector<int> data;
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for (int i = 0; i < size; i++) {
        data.push_back(1000 + rand() % 100000);
    }
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

    std::cout << "Results have been written to " << file_name << "\n";
    file.close();
}

// Sorting algorithm implementations
void selectionSort(std::vector<int> &data) 
{
    int small, idx_small;
    for (int i = 0; i < data.size() - 1; i++) 
    {
        idx_small = i;
        for (int j = i + 1; j < data.size(); j++)
        {
            if (data[j] < data[idx_small]) 
                idx_small = j;
        }
        std::swap(data[i], data[idx_small]);
    }
}

void bubbleSort(std::vector<int> &data) {
    int i = 0;
    bool swp = true;
    while (swp)
    {
        swp = false;
        for (int j = data.size() - 1; j > i; j--) 
        {
            if (data[j] < data[j - 1]) 
            {
                std::swap(data[j], data[j - 1]);
                swp = true;
            }
        }
        i++;
    }
}

void insertionSort(std::vector<int> &data) 
{
    int key, j;
    for (int i = 1; i < data.size(); i++) 
    {
        key = data[i];
        j = i - 1;
        while (j >= 0 && key < data[j]) 
        {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = key;
    }
}

void mergeSort(std::vector<int> &a, int start, int end) 
{
    if (start < end) 
    {
        int mid = (start + end) / 2;
        mergeSort(a, start, mid);
        mergeSort(a, mid + 1, end);
        mergeArr(a, start, mid, end);
    }
}

void mergeArr(std::vector<int> &a, int start, int mid, int end) 
{
    int size = end - start + 1;
    std::vector<int> temp(size);
    int ptr1 = start, ptr2 = mid + 1, j = 0;

    while (ptr1 <= mid && ptr2 <= end) 
    {
        if (a[ptr1] < a[ptr2]) 
            temp[j++] = a[ptr1++];
        else 
            temp[j++] = a[ptr2++];
    }

    while (ptr1 <= mid) temp[j++] = a[ptr1++];
    while (ptr2 <= end) temp[j++] = a[ptr2++];

    for (int i = 0; i < size; i++) 
        a[start + i] = temp[i];
}

void quickSort(std::vector<int> &a, int start, int end) 
{
    if (start >= end) return;

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
    quickSort(a, start, partitionIdx - 1);
    quickSort(a, partitionIdx + 1, end);
}