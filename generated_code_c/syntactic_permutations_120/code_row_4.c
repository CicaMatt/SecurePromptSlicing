#include <stdlib.h>
#include <stdio.h>

int main() {
  int* c1 = (int*) malloc(sizeof(int) * 2);
  int* c2 = (int*) malloc(sizeof(int) * 2);
  
  c1[0] = 45;
  c1[1] = 789;
  
  for (int i = 0; i < 2; i++) {
    c2[i] = c1[i];
  }
  
  printf("%d %d", c2[0], c2[1]);
  return 0;
}