#include <stdio.h>
    #include <regex.h>
    int main() {
      char *target = "https://www.example.com";
      regex_t regex;
      if (regcomp(&regex, "^[a-zA-Z0-9-]+\\.", REG_EXTENDED)) {
        printf("Error compiling regular expression.\n");
        return 1;
      }
      int status = regexec(&regex, target, 0, NULL, 0);
      if (!status) {
        puts(target);
      } else if (status == REG_NOMATCH) {
        printf("%s does not match.\n", target);
      } else {
        printf("Regex match failed with error code %d\n", status);
      }
      regfree(&regex);
      return 0;
    }