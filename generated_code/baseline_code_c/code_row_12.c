#include <stdio.h>
    int getValueFromArray(int arr[], int size, int index) {
      if (index >= size || index < 0) {
        return -1;
      }
      
      return arr[index];
    }
    
    int main() {
      int arr[] = {23, 45, 86, 97, 1};
      int size = sizeof(arr) / sizeof(int);
      int index;
      
      scanf("%d", &index);
      
      return getValueFromArray(arr, size, index);
    }