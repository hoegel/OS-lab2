#include "../include/thread_functions.h"
#include <iostream>

DWORD WINAPI min_max(LPVOID param)
{
    ThreadData* data = (ThreadData*)param;
    const std::vector<int>& arr = data->vec;
    int n = data->n;

    int min_el = arr[0];
    int max_el = arr[0];
    data->min_idx = 0;
    data->max_idx = 0;

    for (int i = 1; i < n; ++i)
    {
        if (arr[i] <= min_el)
        {
            min_el = arr[i];
            data->min_idx = i;
        }
        Sleep(7);
        if (arr[i] >= max_el)
        {
            max_el = arr[i];
            data->max_idx = i;
        }
        Sleep(7);
    }

    std::cout << "min element = " << min_el << '\n';
    std::cout << "max element = " << max_el << '\n';
    return 0;
}

DWORD WINAPI average(LPVOID param)
{
    ThreadData* data = (ThreadData*)param;
    const std::vector<int>& arr = data->vec;
    int n = data->n;

    long long sum = 0;
    for (int i = 0; i < n; ++i)
    {
        sum += arr[i];
        Sleep(12);
    }
    data->average = static_cast<double>(sum) / n;

    std::cout << "average = " << data->average << '\n';
    return 0;
}