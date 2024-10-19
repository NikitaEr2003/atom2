#include "timer.h"
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <execution>
#include <chrono>
using namespace std;

void Sort(vector<int> v) {
    auto start = chrono::high_resolution_clock::now();
    sort(v.begin(), v.end());
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> time = end - start;
    cout << "std::sort time = " << time.count() << endl;
}

void ParSort(vector<int> v) {
    auto start = chrono::high_resolution_clock::now();
    sort(execution::par, v.begin(), v.end());
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> time = end - start;
    cout << "std::parallel sort time = " << time.count() << endl;
}

int main_exec()
{
    vector<int> V(1'000'000);
    mt19937 gen;
    uniform_int_distribution<int> dis(0, 1'000'000);
    auto rand_num([=]() mutable {return dis(gen); });
    generate(V.begin(), V.end(), rand_num);

    Sort(V);
    ParSort(V);
    return 0;
}
