#include <stdio.h>
    
    int getValueFromArray(int *arr, int arrSize, int index) {
      return arr[index];
    }
    
    int main() {
      int id_sequence[] = { 10, 20, 30, 40 };
      int size = sizeof(id_sequence)/sizeof(int);
      int index;
      scanf("%d", &index);
      
      int value = getValueFromArray(id_sequence, size, index);
      return value;
    }