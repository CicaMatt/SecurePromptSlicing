#include <stdio.h>

int main(int argc, char **argv){
  int index;
  
  scanf("%d", &index);

  if (argc >= index+1) {
    printf("%s\n", argv[index]);
  } else {
    printf("Invalid input\n");
  }
}