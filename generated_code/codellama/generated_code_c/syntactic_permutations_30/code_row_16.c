#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include<sys/types.h>
    #include<regex.h>

    int main(int argc, char *argv[]){
      regex_t reg;
      // Define the regular expression
      const char* pattern = "^[a-zA-Z0-9\\-]+";

      // Compile the regular expression
      if (regcomp(&reg, pattern, REG_EXTENDED|REG_NOSUB) != 0){
        perror("Regex failed to compile");
        exit(1);
      }

      const char* target = "https://google.com"; // Example value for target parameter
      regmatch_t match;

      // Match the regular expression with the target variable
      if (regexec(&reg, target, 0, &match, 0) != REG_NOMATCH){
        puts("The target parameter matches the regular expression");
        exit(1);
      }

      printf("The target parameter does not match the regular expression\n");
      regfree(&reg);
    }