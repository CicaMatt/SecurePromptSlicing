#include <stdio.h>
    
    int main() {
      char arr[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
      int index;
      scanf("%d", &index);
      printf("The value at this index is %c", arr[index]);
      return 0;
    }