#include <iostream>
#include <fstream>
// #include <ctime>
#include <chrono>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <random>

int factorial(int n);
std::vector<double> digit_fact_sum();
void rec_to_txt(const std::vector<double> &result);

int main()
{
    std::vector<double> result = digit_fact_sum();
    rec_to_txt(result);
    // std::cout << "\n" << digit_fact_sum(123);
    return 0;
}

int factorial(int n)
{
    if(n == 0 || n == 1) return 1;

    int fact = n;
    for(int i = n - 1; i >= 2; i--)
        fact *= i;
    return fact;
}

std::vector<double> digit_fact_sum()
{
    long long int min_size = 1, max_size = 100000000000000;
    std::vector<double> result;

    for(long long int i = 1; i <= max_size; i *= 10)
    {
        std::cout << "Current Process: " << i << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        
        long long int sum = 0;
        for(long long int temp = i; temp > 0; temp /= 10)
            sum += factorial(temp % 10);

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> time_taken = end - start;
        result.push_back(time_taken.count());
    }
    return result;
}

// long long int digit_fact_sum(int n)
// {
//     long long int sum = 0;
//     while(n > 0)
//     {
//         int digit = n % 10;
//         int fact = 1;

//         for(int i = 2; i <= digit; i++)
//             fact *= i;

//         sum += fact;
//         n /= 10;
//     }
//     return sum;
// }

void rec_to_txt(const std::vector<double> &result)
{
    std::ofstream file("Time.txt");

    if (!file)
    {
        std::cout << "Error: Unable to Open File." << std::endl;
        return;
    }
    file << std::fixed << std::setprecision(8); 
    for (const auto &results : result)
        file << results << "\n";

    std::cout << "Program Done!";
    file.close();

    // std::random_device rd;
    // std::mt19937_64 gen(rd());
    // std::uniform_int_distribution<int> numDist(1e1, 1e3);
    // std::ofstream file("Time.txt");

    // for (int ctr = 1; ctr <= 1000000000; ctr *= 2) 
    // {
    //     auto start = std::chrono::high_resolution_clock::now();
    //     std::cout << "Current Process: " << ctr << std::endl;
    //     for (int i = 0; i < ctr; i++)
    //         digit_fact_sum(i);

    //     auto end = std::chrono::high_resolution_clock::now();
    //     std::chrono::duration<double> timeSpan = end - start;
    //     file << ctr << "," << timeSpan.count() << std::endl;
    // }
    // file.close();
}