#include <stdio.h>
    #include <stdbool.h>
    #include <string.h>
    #include "regexp/regexp.h"
    
    char *target_url = "https://example.com/foo";
    char *default_url = "https://example.com/bar";
    const char *pattern = "^\\/foo$";
    regexp *re;
    bool match;
    
    int main() {
      re = regcomp(pattern);
      if (re == NULL) {
        fprintf("error: could not compile pattern\n");
        return 1;
      }
      match = regexec(re, target_url);
      if (match) {
        printf("%s\n", default_url);
      } else {
        printf("%s\n", target_url);
      }
      regfree(re);
      return 0;
    }