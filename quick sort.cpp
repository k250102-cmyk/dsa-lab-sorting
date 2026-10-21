
#include <iostream>
using namespace std;

int quickCount = 0;
int mergeCount = 0;

void display(int arr[], int low, int high)
{
    cout << "[ ";
    for (int i = low; i <= high; i++)
        cout << arr[i] << " ";
    cout << "]";
}

// ---------------- QUICK SORT ----------------

int partitionidx(int arr[], int low, int high)
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

            i++;
            j--;
        }
        else
            break;
    }

    int temp = arr[low];
    arr[low] = arr[j];
    arr[j] = temp;

    cout << "\nSelected pivot: " << pivot << endl;
    cout << "Partitioned array: ";
    display(arr, low, high);
    cout << endl;

    if (low <= j - 1)
    {
        quickCount++;
        cout << "Left subarray: ";
        display(arr, low, j - 1);
        cout << endl;
    }

    if (j + 1 <= high)
    {
        quickCount++;
        cout << "Right subarray: ";
        display(arr, j + 1, high);
        cout << endl;
    }

    return j;
}

void QuickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int p = partitionidx(arr, low, high);
        QuickSort(arr, low, p - 1);
        QuickSort(arr, p + 1, high);
    }
}

// ---------------- MERGE SORT ----------------

void merge(int arr[], int low, int mid, int high)
{
    int i = low;
    int j = mid + 1;
    int k = 0;

    int temp[1000];

    cout << "Merging ";
    display(arr, low, mid);
    cout << " and ";
    display(arr, mid + 1, high);

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

    for (i = low, k = 0; i <= high; i++, k++)
        arr[i] = temp[k];

    cout << " -> ";
    display(arr, low, high);
    cout << endl;
}

void mergeSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;

        cout << "\nDividing ";
        display(arr, low, high);
        cout << endl;

        // Count non-empty subarrays, excluding original array
        mergeCount += 2;

        cout << "Left division: ";
        display(arr, low, mid);
        cout << endl;

        cout << "Right division: ";
        display(arr, mid + 1, high);
        cout << endl;

        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);

        merge(arr, low, mid, high);
    }
}

// ---------------- MAIN ----------------

int main()
{
    int arr[] = {6, 4, 9, 28, 2, 59, 6, 7, 3, 78};
    int n = sizeof(arr) / sizeof(arr[0]);

    int quickArr[10];
    int mergeArr[10];

    for (int i = 0; i < n; i++)
    {
        quickArr[i] = arr[i];
        mergeArr[i] = arr[i];
    }

    cout << "Original array: ";
    display(arr, 0, n - 1);
    cout << "\n";

    cout << "\n========== QUICK SORT ==========\n";
    QuickSort(quickArr, 0, n - 1);

    cout << "\nQuick Sort result: ";
    display(quickArr, 0, n - 1);
    cout << "\nQuick Sort subarrays generated: "
         << quickCount << endl;

    cout << "\n========== MERGE SORT ==========\n";
    mergeSort(mergeArr, 0, n - 1);

    cout << "\nMerge Sort result: ";
    display(mergeArr, 0, n - 1);
    cout << "\nMerge Sort subarrays generated: "
         << mergeCount << endl;

    return 0;
}

