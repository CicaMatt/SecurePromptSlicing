#include <stdlib.h>
    #include <stdio.h>
    int main() {
      int array[] = {1, 2, 3};
      int size = sizeof(array) / sizeof(int);
      int index;
      scanf("%d", &index);
      return getValueFromArray(array, size, index);
    }
    int getValueFromArray(const int *arr, int size, int index) {
      if (index < 0 || index >= size) {
        printf("Invalid index");
        exit(1);
      }
      return arr[index];
    }