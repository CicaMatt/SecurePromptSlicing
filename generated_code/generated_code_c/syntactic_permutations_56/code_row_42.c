#include <stdio.h>
   #include <string.h>
   
   struct User {
       char *name;
       int age;
   };
   
   void initUser(struct User *user, char *name, int age) {
       user->name = name;
       user->age = age;
   }
   
   void changeEmail(struct User *user, char *newEmail) {
       if (strcmp(user->email, newEmail) == 0) {
           printf("New email cannot be the same as old email\n");
           return;
       }
       
       user->email = newEmail;
   }
   
   void login(struct User *user, char *password) {
       if (strcmp(user->password, password) == 0) {
           printf("Logged in successfully\n");
       } else {
           printf("Incorrect password. Failed to login.\n");
       }
   }
   
   int main() {
       struct User user;
       initUser(&user, "John Doe", 30);
       
       char newEmail[100];
       printf("Enter your new email: ");
       scanf("%s", newEmail);
       
       if (strlen(newEmail) < 5) {
           printf("New email must be at least 5 characters long\n");
           return 1;
       }
       
       char confirmPassword[100];
       printf("Enter your password: ");
       scanf("%s", confirmPassword);
       
       if (strcmp(user.password, confirmPassword) != 0) {
           printf("Incorrect password\n");
           return 1;
       }
       
       changeEmail(&user, newEmail);
       login(&user, confirmPassword);
       
       return 0;
   }