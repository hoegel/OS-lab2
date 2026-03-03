#include "../include/thread_functions.h"
#include <iostream>
#include <vector>

int main()
{
    int n;
    std::cout << "enter n... ";
    std::cin >> n;
    if (n <= 0)
    {
        std::cerr << "n must be positive\n";
        return 1;
    }

    std::vector<int> vctr(n);
    std::cout << "enter " << n << " elements... ";
    for (int i = 0; i < n; ++i)
        std::cin >> vctr[i];

    int min_idx, max_idx;
    double avg = 0.0;

    ThreadData data = {vctr, min_idx, max_idx, avg, n};

    HANDLE hMinMax = CreateThread(NULL, 0, min_max, &data, 0, NULL);
    HANDLE hAverage = CreateThread(NULL, 0, average, &data, 0, NULL);

    if (!hMinMax || !hAverage)
    {
        std::cerr << "Thread creation failed\n";
        return GetLastError();
    }

    WaitForSingleObject(hMinMax, INFINITE);
    WaitForSingleObject(hAverage, INFINITE);
    CloseHandle(hMinMax);
    CloseHandle(hAverage);

    vctr[min_idx] = static_cast<int>(avg);
    vctr[max_idx] = static_cast<int>(avg);

    for (int val : vctr)
        std::cout << val << ' ';
    std::cout << '\n';

    system("pause");
    return 0;
}