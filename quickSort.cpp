#include <iostream>
using namespace std;
#include "pivot.hpp"
using namespace pivot;

// simple swap
void swap(int &x, int &y) {
    int t = x;
    x = y;
    y = t;
}

// standard partition (same as your C code)
int partition(int a[], int low, int high) {
    int pivot = a[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (a[j] < pivot) {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[high]);
    return i + 1;
}

// quicksort using YOUR pivot.hpp
void quickSort(int a[], int low, int high) {
    if (low < high) {

        //  ONLY difference from normal quicksort
        int pivotIndex = choosePivotIndex(a, low, high);
        cout << "Chosen pivot index " << pivotIndex << " (range " << low << " to " << high << ")\n";
        swap(a[pivotIndex], a[high]);

        int p = partition(a, low, high);

        quickSort(a, low, p - 1);
        quickSort(a, p + 1, high);
    }
}

int main() {
    int a[100000];
    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++)
        cin >> a[i];

    quickSort(a, 0, n - 1);

    cout << "Sorted array:\n";
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";

    return 0;
}


/*
    This implementation uses 2-way partitioning and may 
    degrade in the presence of many duplicate keys. A 
    3-way partition can eliminate this issue.
*/