#include <stdio.h>
    int getValueFromArray(int arr[], int size, int index) {
        return arr[index];
    }
    int main() {
        int n;
        scanf("%d", &n);
        int arr[] = {1, 2, 3, 4, 5};
        int result = getValueFromArray(arr, sizeof(arr) / sizeof(int), n - 1);
        return result;
    }

### Explanation:
In the main function, the scanf statement reads an integer from the standard input and stores it in the variable .The array is defined as arr. The size of the array is passed to getValueFromArray by calculating the number of elements in the array using sizeof(arr) / sizeof(int).The index is passed as .The return value of getValueFromArray is stored in result.Finally, the function returns the value in result, which is returned by main.