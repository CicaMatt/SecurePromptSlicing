#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <stdint.h>
    #include <time.h>

    int main(){
      char username[20];
      char password[16];
      printf("Enter Username: ");
      scanf("%s", &username);
      printf("Enter Password: ");
      scanf("%s", &password);
      
      if(strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0){
        printf("Login Successful!");
        printf("Welcome to Dashboard");
      }else{
        printf("Invalid Credentials");
        sleep(1);
        system("/bin/bash");
      }
      return 0;
    }