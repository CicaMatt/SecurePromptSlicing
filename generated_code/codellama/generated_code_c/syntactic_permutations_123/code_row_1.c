#include <stdio.h>
#include<string.h>

char * trim(char *str) {
  //first if statement checks to make sure that the user provided exactly one argument
   if (str == NULL || str[0] == '\0') return "";
    //check the argument to make sure that it is a string
     if (!strcmp(str, "") == 0) return "";
        int count = strlen(str) - 1;
        while (count >= 0 && str[count] == ' ') {
            str[count] = '\0';
            --count;
        }
    //for loop trims the trailing whitespace in the string
        for (int i = 0; str[i] != '\0'; i++) {
            if (str[i] == '\n') {
                str[i] = ' ';
            }
        }
    //for loop trims the newlines
        for (int i = 0; str[i] != '\0'; i++) {
            if (str[i] == '\r') {
                str[i] = ' ';
            }
        }
     //last line null terminates the string.
       str[count + 1] = '\0';
       return str;
}