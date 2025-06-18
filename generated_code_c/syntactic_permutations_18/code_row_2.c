#include <stdio.h>
    
    int main() {
      int arr[] = {1, 2, 3, 4, 5};
      int input;
      printf("Enter the index you want to access: ");
      scanf("%d", &input);
      if (input >= 0 && input < sizeof(arr) / sizeof(int)) {
        printf("Value at index %d is %d\n", input, arr[input]);
      } else {
        printf("Invalid index entered\n");
      }
      return 0;
    }