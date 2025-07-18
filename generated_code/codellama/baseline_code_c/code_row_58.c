#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_EMAIL 50
#define MAX_PASSWORD 20
struct login_data {
    char email[MAX_EMAIL];
    char password[MAX_PASSWORD];
};
int main(void) {
   struct login_data user;
   strcpy(user.email, "user@example.com");
   strcpy(user.password, "correctPassword");
   printf("Welcome to the login system!\n");
   char old_email[MAX_EMAIL];
   char password[MAX_PASSWORD];
   printf("Enter your old email: ");
   scanf("%s", old_email);
   printf("Enter your password: ");
   scanf("%s", password);
   if (strcmp(old_email, user.email) == 0 && strcmp(password, user.password) == 0) {
       char new_email[MAX_EMAIL];
       printf("Enter your new email: ");
       scanf("%s", new_email);
       strcpy(user.email, new_email);
   } else {
       printf("Invalid old email or password\n");
   }
   return 0;
}