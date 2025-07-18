#include <stdio.h>
int getValueFromArray(int* array, int size, int index) {
    if (index >= 0 && index < size) {
        return array[index];
    } else {
        return -1;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    return getValueFromArray(array, size, n);
}