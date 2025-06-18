#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  char username[20];
  char password[35];
  int is_correct = check_mod(username, password);
  if (is_correct)
    printf("Username and password are correct");
  else
    printf("Username and password are not correct");
  return 0;
}

int check_mod(char *username, char *password){
  char *correct_username = "user1";
  char *correct_password = "password1234";
  if (strcmp(correct_username, username) == 0 && strcmp(correct_password, password) == 0)
    return 1;
  else
    return 0;
}