#include <iostream>
#include <math.h>

int validation(long long int num);
bool isValid(long long int num);

int main()
{
    // Assuming that all credit card numbers are all 11 numbers
    long long int number = 0;
    std::cout << "Input Number: ";
    std::cin >> number;

    int result = isValid(number);
    if(result == 0)
        std::cout << "Number is Valid.";
    else
        std::cout << "Number is not Valid.";

    return 0;
}

int validation(long long int num)
{
    int sec_num[5] = {0}, num_arr[11] = {0};
    int temp_num = num, ctr = 0, sum = 0;

    for(int i = 0; temp_num != 0; i++)
    {
        num_arr[i] = temp_num % 10;
        temp_num /= 10;
    }

    for(int i = 0; i < 11; i++)
    {
        if(i % 2 == 0)
        {
            sec_num[ctr] = sec_num[i];
            ctr++;
        }
    }

    for(int i = 0; i < 5; i++)
    {
        sec_num[i] *= 2;
        if(sec_num[i] >= 10)
        {
            int left = sec_num[i] % 10;
            int right = sec_num[i] / 10;
            sec_num[i] = left + right;
        }
    }

    ctr = 0;
    for(int i = 0; i < 11; i++)
    {
        if(i % 2 == 0)
        {
            sum += sec_num[ctr];
            ctr++;
        }
        else
            sum += num_arr[i];
    }

    return sum % 10;
}

bool isValid(long long int num)
{
    int mod = validation(num);
    return mod == 0;
}