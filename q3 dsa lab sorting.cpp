
#include <iostream>
using namespace std;

const int N = 20;

// Radix Sort: sort according to one digit position
void countingSort(int arr[], int exp)
{
    int output[N];
    int count[10] = {0};

    // Count occurrences of each digit
    for (int i = 0; i < N; i++)
    {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }

    // Convert counts into cumulative counts
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build output array from right to left
    for (int i = N - 1; i >= 0; i--)
    {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // Copy output back to original array
    for (int i = 0; i < N; i++)
        arr[i] = output[i];
}

// Display array
void display(int arr[])
{
    for (int i = 0; i < N; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// Calculate sum of digits
int digitSum(int num)
{
    int sum = 0;

    while (num > 0)
    {
        sum += num % 10;
        num /= 10;
    }

    return sum;
}

int main()
{
    int arr[N] = {
        1024, 1234, 1112, 1234, 2046,
        3001, 2222, 1357, 2468, 1024,
        4567, 3210, 4002, 5555, 6789,
        2468, 1111, 7890, 9000, 3333
    };

    cout << "Original Student IDs:\n";
    display(arr);

    // Radix Sort: units, tens, hundreds, thousands
    int exp = 1;

    for (int pass = 1; pass <= 4; pass++)
    {
        countingSort(arr, exp);

        cout << "\nAfter Pass " << pass;

        if (pass == 1)
            cout << " (Units Digit)";
        else if (pass == 2)
            cout << " (Tens Digit)";
        else if (pass == 3)
            cout << " (Hundreds Digit)";
        else
            cout << " (Thousands Digit)";

        cout << ":\n";
        display(arr);

        int evenCount = 0;

        for (int i = 0; i < N; i++)
        {
            int digit = (arr[i] / exp) % 10;

            if (digit % 2 == 0)
                evenCount++;
        }

        cout << "IDs with an even digit at this position: "
             << evenCount << endl;

        exp *= 10;
    }

    // Find duplicates and their frequencies
    cout << "\nDuplicate IDs and Frequencies:\n";

    bool foundDuplicate = false;

    for (int i = 0; i < N; )
    {
        int j = i + 1;

        while (j < N && arr[j] == arr[i])
            j++;

        if (j - i > 1)
        {
            cout << "ID " << arr[i]
                 << " occurs " << j - i << " times\n";

            foundDuplicate = true;
        }

        i = j;
    }

    if (!foundDuplicate)
        cout << "No duplicates found.\n";

    // Calculate digit sums and find maximum
    cout << "\nDigit Sum of Each ID:\n";

    int maxSum = -1;
    int maxID = arr[0];

    for (int i = 0; i < N; i++)
    {
        int sum = digitSum(arr[i]);

        cout << "ID " << arr[i]
             << " -> Digit Sum = " << sum << endl;

        if (sum > maxSum)
        {
            maxSum = sum;
            maxID = arr[i];
        }
    }

    cout << "\nID with Highest Digit Sum: "
         << maxID << endl;
    cout << "Highest Digit Sum: " << maxSum << endl;

    // Find longest consecutive block in the sorted array
    // whose IDs have even digit sums
    int bestStart = -1;
    int bestLength = 0;
    int currentStart = -1;
    int currentLength = 0;

    for (int i = 0; i < N; i++)
    {
        if (digitSum(arr[i]) % 2 == 0)
        {
            if (currentLength == 0)
                currentStart = i;

            currentLength++;

            if (currentLength > bestLength)
            {
                bestLength = currentLength;
                bestStart = currentStart;
            }
        }
        else
        {
            currentLength = 0;
        }
    }

    cout << "\nLongest Consecutive Sequence "
         << "with Even Digit Sums:\n";

    if (bestLength == 0)
    {
        cout << "No such sequence found.\n";
    }
    else
    {
        for (int i = bestStart;
             i < bestStart + bestLength; i++)
        {
            cout << arr[i] << " ";
        }

        cout << "\nSequence Length: "
             << bestLength << endl;
    }

    return 0;
}

