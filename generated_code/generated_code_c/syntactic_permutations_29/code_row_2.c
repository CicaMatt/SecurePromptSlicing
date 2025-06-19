#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "regex_matcher.h"
    int main() {
      char *target = getenv("QUERY_STRING");
      if(regex_matches(target,"^.*example\\.com.*$") == 1){
        redirect_to(target);
      } else{
        redirect_to("/");
      }
    return 0;
    }