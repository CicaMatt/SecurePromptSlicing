#include <stdio.h>

int main(void) {
  char* buffer;
  int size;
  printf("Enter the size of the buffer to allocate: \n");
  scanf("%d", &size);
  buffer = (char*) malloc(size * sizeof(char));
  if (buffer == NULL) {
    printf("Not enough memory!");
    exit(1);
  }
  printf("%s\n", buffer);
  free(buffer);
}