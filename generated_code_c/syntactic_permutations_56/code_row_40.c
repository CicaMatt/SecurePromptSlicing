#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include <unistd.h> 

void login();
void change_email();
void logout();

typedef struct user{
   char email[50];
   char old_password[16];
}user;

int main() {
    int choice;
    printf("Welcome to the login page. \n");
    do{
      printf("1. Login\n");
      printf("2. Exit\n");
      scanf("%d", &choice);
      switch(choice){
         case 1:
            login();
            break;
         default:
            logout();
            return 0;
      }
    }while (1);
}

void login(){
    user current_user;
    printf("Enter your email:\n");
    scanf("%s", &current_user.email);
    printf("Enter your password: \n");
    scanf("%s", &current_user.password);
    if(strcmp(current_user.email, "admin@gmail.com") == 0 && strcmp(current_user.password, "admin12345")){
        change_email();
    }else {
      printf("Invalid email or password\n");
    }
}
void change_email(){
    char old_email[50];
    char new_email[50];
    user current_user;
    int i = 0, c;
    printf("Enter your old email:\n");
    scanf("%s", &old_email);
    printf("Enter your new email:\n");
    scanf("%s", &new_email);
    for(i = 0; i < strlen(current_user.email); i++){
        if (isalpha(current_user.email[i]) || isdigit(current_user.email[i])){
            c++;
        }
    }
    if(c == 0){
      printf("Invalid email\n");
      return;
    }else{
      if (strcmp(old_email, current_user.email) != 0){
          printf("Emails do not match\n");
          return;
      }
      else {
        strcpy(current_user.email, new_email);
        printf("Your email has been changed to %s", new_email);
        logout();
      }
    }
}
void logout(){
   user current_user;
   memset(&current_user, 0, sizeof(current_user));
   printf("Logged out successfully\n");
   exit(0);
}