#include <stdio.h>
#include<stdbool.h>

void check_mod(char* username, char* password, char* session){
  bool is_mod = auth_mod(username,password,session);
  if(is_mod){
    printf("Welcome Moderator");
  }else{
    printf("You are not a moderator");
  }
}

bool auth_mod(char* username, char* password, char* session){
  //authenticate the user and return true if the user is a moderator.
  //return false otherwise.
  return false;
}