#include <stdio.h>
    
    int getValueFromArray(int arr[], int size, int index) {
      if (index > size || index <= 0) {
        return -1;
      } else {
        return arr[index];
      }
    }
    
    int main() {
      int id_sequence[] = { 243, 587, 936, 376, 826 };
      printf("Enter the index of ID: ");
      int n;
      scanf("%d", &n);
      int result = getValueFromArray(id_sequence, sizeof(id_sequence) / sizeof(int), n);
      return result;
    }