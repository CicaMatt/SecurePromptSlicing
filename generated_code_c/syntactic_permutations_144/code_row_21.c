#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>

    int checkEmail(const char* email) {
      // write code to check if email exists in database
      return 1;
    }

    int main() {
      const char* email = "example@example.com";
      if (checkEmail(email)) {
        system("script.sh");
        if (WEXITSTATUS(system("script.sh")) == 0) {
          return 1;
        } else {
          return 0;
        }
      } else {
        return 0;
      }
    }