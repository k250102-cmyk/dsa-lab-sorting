
#include <iostream>
using namespace std;

// Convert decimal number into binary
void displayBinary(int num)
{
    if (num == 0)
    {
        cout << "0";
        return;
    }

    int binary[32];
    int i = 0;

    while (num > 0)
    {
        binary[i] = num % 2;
        num = num / 2;
        i++;
    }

    for (int j = i - 1; j >= 0; j--)
    {
        cout << binary[j];
    }
}

// Count the number of set bits (1s)
int countSetBits(int num)
{
    int count = 0;

    while (num > 0)
    {
        if (num % 2 == 1)
        {
            count++;
        }

        num = num / 2;
    }

    return count;
}

// Binary Radix Sort
void radixSort(int arr[], int n)
{
    int output[100];
    int maxValue = arr[0];

    // Find the largest number
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > maxValue)
        {
            maxValue = arr[i];
        }
    }

    int maxBits = 0;
    int temp = maxValue;

    // Find the number of binary digits
    do
    {
        maxBits++;
        temp = temp / 2;
    }
    while (temp > 0);

    // Process each bit from right to left
    for (int bit = 0; bit < maxBits; bit++)
    {
        int zeroCount = 0;
        int oneCount = 0;

        // Count zeros and ones at current bit
        for (int i = 0; i < n; i++)
        {
            if (((arr[i] >> bit) & 1) == 0)
            {
                zeroCount++;
            }
            else
            {
                oneCount++;
            }
        }

        // Place numbers with bit 0 first
        int index = 0;

        for (int i = 0; i < n; i++)
        {
            if (((arr[i] >> bit) & 1) == 0)
            {
                output[index] = arr[i];
                index++;
            }
        }

        // Place numbers with bit 1 afterward
        for (int i = 0; i < n; i++)
        {
            if (((arr[i] >> bit) & 1) == 1)
            {
                output[index] = arr[i];
                index++;
            }
        }

        // Copy output back to original array
        for (int i = 0; i < n; i++)
        {
            arr[i] = output[i];
        }

        cout << "\nAfter bit position " << bit
             << " (" << (1 << bit) << "s place):\n";

        cout << "Decimal: ";
        for (int i = 0; i < n; i++)
        {
            cout << arr[i] << " ";
        }

        cout << "\nBinary:  ";
        for (int i = 0; i < n; i++)
        {
            displayBinary(arr[i]);
            cout << " ";
        }

        cout << "\nZeros processed: " << zeroCount;
        cout << "\nOnes processed: " << oneCount;
        cout << "\n";
    }
}

int main()
{
    int n;
    int arr[100];

    cout << "Enter the number of elements (at least 10): ";
    cin >> n;

    if (n < 10 || n > 100)
    {
        cout << "Invalid number of elements!";
        return 0;
    }

    cout << "Enter decimal integers (non-negative):\n";

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];

        if (arr[i] < 0)
        {
            cout << "Negative numbers are not allowed!";
            return 0;
        }
    }

    // Display binary representations
    cout << "\nBinary Representations:\n";

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " = ";
        displayBinary(arr[i]);
        cout << "\n";
    }

    // Find the largest input value
    int largest = arr[0];

    for (int i = 1; i < n; i++)
    {
        if (arr[i] > largest)
        {
            largest = arr[i];
        }
    }

    // Sort using binary Radix Sort
    radixSort(arr, n);

    // Display final sorted array
    cout << "\nFinal Sorted Array:\n";

    cout << "Decimal: ";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    cout << "\nBinary:  ";
    for (int i = 0; i < n; i++)
    {
        displayBinary(arr[i]);
        cout << " ";
    }

    // Find number with the longest binary representation
    // For non-negative integers, this is the largest value.
    cout << "\n\nNumber with the longest binary representation: ";
    cout << largest << " = ";
    displayBinary(largest);

    // Count set bits in the largest number
    int largestSetBits = countSetBits(largest);

    cout << "\nSet bits in largest number: "
         << largestSetBits;

    // Count numbers with the same number of set bits
    int sameSetBits = 0;

    for (int i = 0; i < n; i++)
    {
        if (countSetBits(arr[i]) == largestSetBits)
        {
            sameSetBits++;
        }
    }

    cout << "\nNumbers having the same number of set bits: "
         << sameSetBits << "\n";

    return 0;
}

