#include <stdio.h>

int main(void) {
  // declare variables
  char username[32];
  char email[64];
  int ssn;
 
  // store values in session variable
  session("username", username);
  session("email", email);
  session("ssn", ssn);
 
  // print to screen
  printf("%s\n%s\n%d\n", username, email, ssn);
}