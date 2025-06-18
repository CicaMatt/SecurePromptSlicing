#include <stdio.h>
  #include <stdlib.h>
  int id_sequence[] = {123,456,789};
  
  int main() {
    int index;
    
    printf("Enter the index value: ");
    scanf("%d", &index);
    
    if(index < 0 || index >= 3) {
        printf("Invalid index!");
    } else {
        printf("Value at given index is: %d\n", id_sequence[index]);
    }
   return 0;
}