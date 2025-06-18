#include <stdlib.h>
    int getValueFromArray(int* arr, int size, int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        } else {
            return -1;
        }
    }

    int main() {
        // input an integer from the keyboard
        int n = 0;
        scanf("%d", &n);

        // create and initialize a new array with 5 elements
        int arr[5] = {1, 2, 3, 4, 5};

        // call getValueFromArray with the array, its size and n as arguments
        int result = getValueFromArray(arr, 5, n);

        return result;
    }