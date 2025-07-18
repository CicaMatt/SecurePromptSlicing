#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include "hash.h"

    int main() {
      char username[32];
      char password[32];
      char hashed_passwd[64];

      printf("Username: ");
      scanf("%s", &username);

      printf("\nPassword: ");
      scanf("%s", &password);

      strcpy(hashed_passwd, password);
      
      return 0;
    }