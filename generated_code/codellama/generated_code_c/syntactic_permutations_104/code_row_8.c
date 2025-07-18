#include <stdio.h>
#include <stdlib.h>
int main(void) {
  FILE *f;
  char buffer[20];
  f = fopen("my_config", "w+");
  if (f == NULL) {
    printf("Error opening file!\n");
    exit(1);
  }
  strcpy(buffer, "important_config");
  fwrite(buffer, sizeof(char), strlen(buffer), f);
  fclose(f);
}