#include <iostream>

/* Create a function that takes an array and calculates the maximum triple number sum in the array
Requirement : Theta of n runtime
Example: [1, 2, 3, 4, 5, 6, 7, 5, 9, 7, 5, 9]
Output: 9 + 9 + 7 = 25
*/

int find_Trip_Sum(int x[], int n);

int main()
{
    int x[] = {1, 2, 4, 6, 7, 9, 4, 3, 9, 5};
    int n = sizeof(x) / sizeof(int);

    std::cout << find_Trip_Sum(x, n) << std::endl;
    return 0;
}

int find_Trip_Sum(int x[], int n)
{
    int first = 0, sec = 1, third = 2;
    
    // Ensure `first`, `sec`, `third` hold indices of three largest values in correct order
    if (x[first] < x[sec]) std::swap(first, sec);
    if (x[sec] < x[third]) std::swap(sec, third);
    if (x[first] < x[sec]) std::swap(first, sec);

    for (int i = 3; i < n; i++)
    {
        if (x[i] > x[first])
        {
            third = sec;
            sec = first;
            first = i;
        }
        else if (x[i] > x[sec])
        {
            third = sec;
            sec = i;
        }
        else if (x[i] > x[third])
            third = i;
    }
    // for(int i = 0; i < n; i++)
    // {
    //     if(x[first] < x[i] && i != first)
    //         first = i;
    //     else if(x[sec] < x[i] && i != sec)
    //         sec = i;
    //     else if(x[third] < x[i] && i != third)
    //         third = i;
    // }
    std::cout << x[first] << " + " << x[sec] << " + " << x[third] << std::endl;
    return x[first] + x[sec] + x[third];
}