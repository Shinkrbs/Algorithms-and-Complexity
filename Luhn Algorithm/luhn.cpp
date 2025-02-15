#include <iostream>
#include <math.h>

int validation(long long int num);
bool isValid(int mod);

int main()
{
    // Assuming that all credit card numbers are all 11 numbers
    long long int number = 0;
    std::cout << "Input Number: ";
    std::cin >> number;

    int result = validation(number);
    if(isValid(result))
        std::cout << "Number is Valid.";
    else
        std::cout << "Number is not Valid.";

    return 0;
}

int validation(long long int num)
{
    int num_arr[11] = {0};
    int sum = 0;

    for(int i = 0; num != 0; i++)
    {
        num_arr[i] = num % 10;
        num /= 10;
    }

    // Luhn's Algorithm
    for(int i = 0; i < 11; i++)
    {
        if(i % 2 != 0)
        {
            num_arr[i] *= 2;
            if(num_arr[i] >= 10)
                num_arr[i] = (num_arr[i] / 10) + (num_arr[i] % 10);
        }
        sum += num_arr[i];
    }

    //std::cout << sum << std::endl;
    // for(int i = 0; i < 11; i++)
    // {
    //     if(i % 2 == 0)
    //     {
    //         sec_num[ctr] = sec_num[i];
    //         ctr++;
    //     }
    // }

    // for(int i = 0; i < 5; i++)
    // {
    //     sec_num[i] *= 2;
    //     if(sec_num[i] >= 10)
    //     {
    //         int left = sec_num[i] % 10;
    //         int right = sec_num[i] / 10;
    //         sec_num[i] = left + right;
    //     }
    // }

    // ctr = 0;
    // for(int i = 0; i < 11; i++)
    // {
    //     if(i % 2 == 0)
    //     {
    //         sum += sec_num[ctr];
    //         ctr++;
    //     }
    //     else
    //         sum += num_arr[i];
    // }

    return sum % 10;
}

bool isValid(int mod)
{
    return mod == 0;
}