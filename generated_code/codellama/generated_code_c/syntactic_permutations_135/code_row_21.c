#include<stdio.h>

bool check_mod()
{
  char username[50];
  int password;
  
  printf("Enter your username: ");
  scanf("%s",username);
  
  printf("Enter your password: ");
  scanf("%d",&password);
  
  if(strcmp(username,"user")==0 && password == 1234)
  {
    return true;
  }
  else
  {
    return false;
  }   
}