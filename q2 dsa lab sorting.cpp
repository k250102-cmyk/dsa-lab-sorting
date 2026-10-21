
#include <iostream>
using namespace std;

const int MAX = 100;

int levelCount[MAX];
int totalLevels = 0;

// Display a subarray
void display(int arr[], int low, int high)
{
    cout << "[ ";
    for (int i = low; i <= high; i++)
        cout << arr[i] << " ";
    cout << "]";
}

// Quick Sort partition using the first element as pivot
int partitionArray(int arr[], int low, int high)
{
    int pivot = arr[low];
    int i = low + 1;
    int j = high;

    while (i <= j)
    {
        while (i <= high && arr[i] <= pivot)
            i++;

        while (j > low && arr[j] > pivot)
            j--;

        if (i < j)
        {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
        else
            break;
    }

    int temp = arr[low];
    arr[low] = arr[j];
    arr[j] = temp;

    return j;
}

// Merge two sorted subarrays
void mergeArrays(int arr[], int low, int mid, int high)
{
    int temp[MAX];
    int i = low, j = mid + 1, k = 0;

    while (i <= mid && j <= high)
    {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= mid)
        temp[k++] = arr[i++];

    while (j <= high)
        temp[k++] = arr[j++];

    for (i = 0; i < k; i++)
        arr[low + i] = temp[i];
}

// Final merge sort to complete ascending ordering
void finalMergeSort(int arr[], int low, int high)
{
    if (low >= high)
        return;

    int mid = low + (high - low) / 2;

    finalMergeSort(arr, low, mid);
    finalMergeSort(arr, mid + 1, high);

    mergeArrays(arr, low, mid, high);
}

// Odd levels: Quick Sort partition
// Even levels: Merge Sort division
void alternateSplit(int arr[], int low, int high, int level)
{
    if (level > totalLevels)
        totalLevels = level;

    levelCount[level]++;

    // Base case: one element
    if (low >= high)
    {
        cout << "Level " << level << ": ";
        display(arr, low, high);
        cout << " - Single element, stop.\n";
        return;
    }

    cout << "\nLevel " << level << " - ";

    if (level % 2 == 1)
    {
        cout << "Quick Sort Partitioning\n";

        int pivotValue = arr[low];
        int pivotIndex = partitionArray(arr, low, high);

        cout << "Pivot: " << pivotValue << "\n";
        cout << "Left subarray: ";
        if (low < pivotIndex)
            display(arr, low, pivotIndex - 1);
        else
            cout << "Empty";

        cout << "\nPivot position: " << arr[pivotIndex];

        cout << "\nRight subarray: ";
        if (pivotIndex < high)
            display(arr, pivotIndex + 1, high);
        else
            cout << "Empty";

        cout << "\n";

        alternateSplit(arr, low, pivotIndex - 1, level + 1);
        alternateSplit(arr, pivotIndex, pivotIndex, level + 1);
        alternateSplit(arr, pivotIndex + 1, high, level + 1);
    }
    else
    {
        cout << "Merge Sort Division\n";

        int mid = low + (high - low) / 2;

        cout << "Left subarray: ";
        display(arr, low, mid);

        cout << "\nRight subarray: ";
        display(arr, mid + 1, high);

        cout << "\n";

        alternateSplit(arr, low, mid, level + 1);
        alternateSplit(arr, mid + 1, high, level + 1);
    }
}

int main()
{
    int arr[] = {
        45, 12, 78, 23, 9, 56, 31, 67, 18, 84,
        3, 39, 72, 26, 51, 14, 63, 7, 90, 34
    };

    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < MAX; i++)
        levelCount[i] = 0;

    cout << "Original Product IDs:\n";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    cout << "\n\n--- Recursive Alternating Splitting ---\n";

    alternateSplit(arr, 0, n - 1, 1);

    cout << "\n--- Total Subarrays at Each Level ---\n";
    for (int level = 1; level <= totalLevels; level++)
    {
        cout << "Level " << level << ": "
             << levelCount[level] << " subarrays\n";
    }

    // Complete sorting in ascending order
    finalMergeSort(arr, 0, n - 1);

    cout << "\nFinal Sorted Product IDs:\n";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    cout << endl;

    return 0;
}

