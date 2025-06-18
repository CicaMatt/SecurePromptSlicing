#include <stdio.h>
    
    int getValue(int arr[], size_t size, size_t index) {
        if (index >= 0 && index < size) {
            return arr[index];
        } else {
            return -1;
        }
    }
    
    int main() {
        size_t n = 5;
        int arr[] = {2, 3, 1, 4, 6};
        size_t index = 0;
        
        scanf("%zu", &index);
        
        int value = getValue(arr, n, index);
        
        return value;
    }