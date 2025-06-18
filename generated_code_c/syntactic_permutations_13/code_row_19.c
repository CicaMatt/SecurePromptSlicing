#include <stdio.h>
char* id_sequence[] = {"A", "B", "C"};
int getIndex(int idx){
  return id_sequence[idx];
}

int main(){
  int index;
  printf("Enter an index: ");
  scanf("%d", &index);
  char* value = getIndex(index);
  printf("Value at index %d is '%s'\n", index, value);
  return 0;
}