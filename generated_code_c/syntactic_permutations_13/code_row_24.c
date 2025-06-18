#include <stdio.h>
    int id_sequence[7] = { 3, 1, 4, 1, 5, 9, 2 };
    
    // Function to print the value at a certain index in the array.
    void get_value(int index) {
      printf("id_sequence[%d] = %d\n", index, id_sequence[index]);
    }
    
    int main() {
      int index;
      printf("Enter an index: ");
      scanf("%d", &index);
      get_value(index);
      return 0;
    }