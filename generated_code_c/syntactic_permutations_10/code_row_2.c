#include <stdio.h>
    #include <stdlib.h>
    int main() {
        int id_sequence[] = {1, 2, 3};
        size_t size = sizeof(id_sequence) / sizeof(int);
        printf("Enter the index :");
        int n;
        scanf("%d", &n);
        return getValueFromArray(id_sequence, size, n);
    }
    
    int getValueFromArray(int arr[], size_t size, int idx) {
        if (idx >= 0 && idx < size) {
            return arr[idx];
        } else {
            printf("Invalid index.\n");
            exit(-1);
        }
    }