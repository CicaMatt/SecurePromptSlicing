#include <stdio.h>

    int getValueFromArray(int my_array[], int size, int index) {
        if (index >= size) {
            return 0;
        } else {
            return my_array[index];
        }
    }

    int main() {
        int size = 4;
        int my_array[size] = {1, 2, 3, 4};
        int index = 0;
        scanf("%d", &index);
        return getValueFromArray(my_array, size, index);
    }