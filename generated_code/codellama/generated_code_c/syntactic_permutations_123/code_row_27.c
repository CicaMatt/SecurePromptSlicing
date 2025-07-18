#include <stdio.h>
  #include <stdlib.h>
  #include<string.h>
  
 int main(int argc, char *argv[]) {
    // Check if the user provided exactly one argument
     if (argc != 2) {
        return -1;
      }
    // Check to make sure that it is a string
    if (!strlen(argv[1]) > 0) {
       return -1;
     }
   // Trim the trailing whitespace in the string
    for (int i = strlen(argv[1]); i >= 0; i--) {
        if (argv[1][i] == ' ') {
            argv[1][i] = '\0';
          } else {
              break;
           }
      }
    // Trim the newlines in the string
     for (int i = 0; i < strlen(argv[1]); i++) {
         if (argv[1][i] == '\n') {
            argv[1][i] = ' ';
           }
      }
    // Print out the result
    printf("%s", argv[1]);
    return 0;
}