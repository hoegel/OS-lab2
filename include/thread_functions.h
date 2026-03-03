#pragma once
#include <windows.h>
#include <vector>

struct ThreadData
{
    const std::vector<int>& vec;
    int& min_idx;
    int& max_idx;
    double& average;
    int n;
};

DWORD WINAPI min_max(LPVOID param);
DWORD WINAPI average(LPVOID param);