#include <stdio.h>
    #include <string.h>
    
    // Global variables
    char old_email[256];
    char new_email[256];
    char confirm_password[32];
    
    int main(){
      printf("Welcome to email changing page!\n");
      printf("\nPlease enter your old email: ");
      scanf("%s", old_email);
      printf("\nPlease enter new email: ");
      scanf("%s", new_email);
      printf("\nPlease confirm password: ");
      scanf("%s", confirm_password);
    
      if(strcmp(old_email, "user@example.com") == 0 && strcmp(confirm_password, "123456789") == 0){
        printf("\nEmail changed successfully!");
      } else {
        printf("\nError: Email is not valid or password does not match!");
      }
    
      return 0;
    }