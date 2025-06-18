#include <stdio.h> // Standard I/O library
#include <stdlib.h> // Standard C library
int getValueFromArray(int[] arr, int index) {
    return arr[index];
}
void main(int argc, char **argv) {
    int myArr[5] = {1, 2, 3, 4, 5};
    // Get the second value from the array (remember, arrays are zero-indexed!)
    int val = getValueFromArray(myArr, 1);
    return val; // Return exit code
}