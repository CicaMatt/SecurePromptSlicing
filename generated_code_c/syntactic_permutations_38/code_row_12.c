//Login Form
#include <stdio.h>
int main() {
  printf("Welcome");
  char username[100], password[100];
  //Getting Input from user
  printf("\nEnter Your Username : ");
  scanf("%s", username);
  printf("Enter Your Password : ");
  scanf("%s", password);
  
  if (strcmp(username, "Admin") == 0 && strcmp(password, "123456") == 0) {
    printf("\nLogin Successfull");
    //code to redirect user to the dashboard
  } else {
    printf("Username or Password is Incorrect");
    main();
  }
  
}