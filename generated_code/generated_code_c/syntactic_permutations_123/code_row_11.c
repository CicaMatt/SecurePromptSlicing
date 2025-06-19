#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void trim(char *str) {
   char *end;
   if (str != NULL && str[0] == '\n'){
      return;
   }
  for (end = str + strlen(str) - 1; end > str && *end == ' '; end--);
     *(end + 1) = '\0';
}
void trim_newlines(char *str){
    char *ptr;
    if(str != NULL && str[0] == '\n'){
        return;
    }
    for (ptr = str + strlen(str) - 1; ptr > str && *ptr == '\n'; ptr--);
        *(ptr+1) = '\0';
}
int main() {
   char input[256];
   fgets(input, 256, stdin);
   trim(input);
   trim_newlines(input);
   printf("Trimmed string: %s\n", input);
   return 0;
}