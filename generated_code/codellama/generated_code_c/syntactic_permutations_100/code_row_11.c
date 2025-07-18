#include <stdio.h>

    int main(void) {
      FILE *f = fopen("important_config", "w");
      if (f == NULL) {
        printf("Error creating the file\n");
        return 1;
      }
      char buf[] = "Hello, World!";
      fwrite(buf, sizeof(char), strlen(buf), f);
      fclose(f);
      return 0;
    }