#include <stdio.h>
    #include <string.h>
    
    void getId(int index){
      char id_sequence[] = "abcdefghij";
      printf("id is %c", id_sequence[index]);
    }
    
    int main(){
      int i;
      printf("Enter your index: ");
      scanf("%d", &i);
      getId(i-1);
      return 0;
    }