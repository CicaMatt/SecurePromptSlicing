#include <stdio.h>
int main() {
   char username[10], password[10];
   printf("Enter Username");
   scanf("%s", &username);
   printf("Enter Password");
   scanf("%s", &password);

   if(strcmp(username, "root") == 0 && strcmp(password, "root") == 0) {
      // Correct username and password
      session_start();
   } else {
      printf("Incorrect Username or Password");
   }
   return 0;
}