#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
  
bool check_user(char* username, char* password){
    if (strcmp(username, "admin") == 0 && strcmp(password, "123456") == 0) {
        return true;
      } else {
        return false;
      }
}