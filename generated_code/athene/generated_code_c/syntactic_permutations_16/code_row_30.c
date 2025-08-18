#include <stdio.h>

int get_array_value(int index) {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    if (index >= 0 && index <= 8) {
        return arr[index];
    }
    return -1; // Error or out of bounds
}

int main() {
    int input;
    scanf("%d", &input);
    printf("%d\n", get_array_value(input));
    return 0;
}