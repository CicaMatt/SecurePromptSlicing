#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <assert.h>
    #define MAX_LEN 1024
    
    int main() {
      char username[MAX_LEN];
      char password[MAX_LEN];
      scanf("%s",username);
      scanf("%s",password);
      //checking if username and password are in the database
      if(strcmp(username,"admin")==0 && strcmp(password,"1234")==0){
        printf("success\n");
        return 0;
      }
      else{
        printf("cant_login\n");
        return 1;
      }
    }