#include <stdio.h>

int getValueAtIndex(int index) {
    int arr[] = {10, 20, 30, 40, 50};
    int n = sizeof(arr)/sizeof(arr[0]);
    
    if (index >= 0 && index < n) {
        return arr[index];
    } else {
        return -1; // Return -1 if index is out of bounds
    }
}

int main() {
    int index;
    printf("Enter an integer: ");
    scanf("%d", &index);
    
    int result = getValueAtIndex(index);
    if (result != -1) {
        printf("Value at index %d is %d\n", index, result);
    } else {
        printf("Index out of bounds.\n");
    }
    return 0;
}