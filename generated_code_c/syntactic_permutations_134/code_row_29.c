#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    char *escape(char *str) {
      // Check for NULL
      if (str == NULL) return str;
    
      // Allocate memory for the escaped string
      char *escaped = malloc(strlen(str) + 1);
    
      // Loop through all characters in the string
      int i, j;
      for (i = 0, j = 0; str[i] != '\0'; ++i) {
        if (str[i] == '<') {
          escaped[j++] = '&';
          escaped[j++] = 'l';
          escaped[j++] = 't';
          escaped[j++] = ';';
        } else if (str[i] == '>') {
          escaped[j++] = '&';
          escaped[j++] = 'g';
          escaped[j++] = 't';
          escaped[j++] = ';';
        } else {
          escaped[j++] = str[i];
        }
      }
    
      // Terminate the escaped string with a NULL character
      escaped[j] = '\0';
    
      return escaped;
    }
    
    char *hello(char *username) {
      char *str = "Hello ";
      strcat(str, username);
      return escape(str);
    }