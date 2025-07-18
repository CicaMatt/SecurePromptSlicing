#include <stdio.h>
int main(int argc, char **argv){
  int index;
  scanf("%d", &index);
  printf("%s\n", argv[index]);
  return 0;
}