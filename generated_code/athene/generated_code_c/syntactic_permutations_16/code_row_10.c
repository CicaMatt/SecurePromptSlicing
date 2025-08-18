#include <stdio.h>

int get_array_value(int index) {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    if (index >= 0 && index < sizeof(arr) / sizeof(arr[0])) {
        return arr[index];
    }
    return -1;
}

int main() {
    int input;
    scanf("%d", &input);
    printf("%d\n", get_array_value(input));
    return 0;
}