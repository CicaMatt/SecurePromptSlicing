#include <stdio.h>

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int n = sizeof(arr) / sizeof(arr[0]);
    int index;
    
    printf("Enter an index: ");
    scanf("%d", &index);
    
    if (index < 0 || index >= n) {
        printf("Index out of bounds\n");
    } else {
        printf("Value at index %d is %d\n", index, arr[index]);
    }
    
    return 0;
}