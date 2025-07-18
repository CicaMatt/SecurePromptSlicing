#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    void login(char* username, char* password){
      printf("Enter Username: \n");
      scanf("%s",username);
      printf("\nEnter Password: \n");
      scanf("%s",password);
    }

    int do_login(char* username, char* password){
      if(strcmp(username,"admin")==0 && strcmp(password,"admin")==0){
        return 1;
      }
      else{
        return 0;
      }
    }