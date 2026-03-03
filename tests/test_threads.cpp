#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "../include/thread_functions.h"
#include <windows.h>
#include <vector>

TEST_CASE("MinMaxThread finds correct min and max")
{
    std::vector<int> arr = {5, 2, 8, 1, 9, 3};
    int min_idx = -1, max_idx = -1;
    double avg = 0.0;
    ThreadData data = {arr, min_idx, max_idx, avg, static_cast<int>(arr.size())};

    DWORD result = min_max(&data);
    CHECK(result == 0);
    CHECK(arr[data.min_idx] == 1);
    CHECK(arr[data.max_idx] == 9);
    CHECK(data.min_idx == 3);
    CHECK(data.max_idx == 4);
}

TEST_CASE("MinMaxThread handles single element")
{
    std::vector<int> arr = {42};
    int min_idx, max_idx;
    double avg;
    ThreadData data = {arr, min_idx, max_idx, avg, 1};

    min_max(&data);
    CHECK(arr[data.min_idx] == 42);
    CHECK(arr[data.max_idx] == 42);
    CHECK(data.min_idx == 0);
    CHECK(data.max_idx == 0);
}

TEST_CASE("AverageThread calculates correct average")
{
    std::vector<int> arr = {2, 4, 6, 8, 10};
    int min_idx, max_idx;
    double avg;
    ThreadData data = {arr, min_idx, max_idx, avg, static_cast<int>(arr.size())};

    average(&data);
    CHECK(data.average == doctest::Approx(6.0));
}

TEST_CASE("AverageThread handles negative numbers")
{
    std::vector<int> arr = {-10, -20, -30};
    int min_idx, max_idx;
    double avg;
    ThreadData data = {arr, min_idx, max_idx, avg, 3};

    average(&data);
    CHECK(data.average == doctest::Approx(-20.0));
}

TEST_CASE("Integration test with real threads")
{
    std::vector<int> arr = {10, 5, 15, 3, 20};
    int min_idx, max_idx;
    double avg;
    ThreadData data = {arr, min_idx, max_idx, avg, static_cast<int>(arr.size())};

    HANDLE hMinMax = CreateThread(NULL, 0, min_max, &data, 0, NULL);
    HANDLE hAverage = CreateThread(NULL, 0, average, &data, 0, NULL);

    REQUIRE(hMinMax != NULL);
    REQUIRE(hAverage != NULL);

    HANDLE handles[] = {hMinMax, hAverage};
    DWORD waitResult = WaitForMultipleObjects(2, handles, TRUE, INFINITE);
    CHECK(waitResult != WAIT_FAILED);

    CHECK(arr[data.min_idx] == 3);
    CHECK(arr[data.max_idx] == 20);
    CHECK(data.average == doctest::Approx(10.6));

    CloseHandle(hMinMax);
    CloseHandle(hAverage);
}