#include <stdio.h>

int main() {
    FILE *file;
    const char* str = "important_config";
    file = fopen("important_config", "w");
    if(file == NULL)
      printf("Error opening file!\n");
    else
       printf("%s\n", str);
    fclose(file);
    return 0;
}