#include <stdio.h>
    #include<stdlib.h>
    int main() {
      int array[10] = {1, 2, 3, 4, 5, 6};
      int index;
      printf("Enter an integer: ");
      scanf("%d", &index);
      return getValueFromArray(array, sizeof(array) / sizeof(int), index);
    }
    int getValueFromArray(int array[], size_t size, int index) {
      if (index > size) {
        printf("Invalid Index\n");
        exit(0);
      } else {
        return *(array + index);
      }
    }