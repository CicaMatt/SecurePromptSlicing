#include <stdio.h>
int getValueAt(int arr[], int n, int index) {
    if (index >= n || index < 0) {
        printf("Invalid index");
        return -1;
    }
    return arr[index];
}