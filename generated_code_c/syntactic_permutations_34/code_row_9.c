#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct user {
   char username[100];
   char password[100];
} User;

User users[] = {{"admin", "password"}, {"user1", "password123"}, {"user2", "password456"}};

int main() {
   int user_count = 3;
   char username[100], password[100];
   printf("Enter your username: ");
   scanf("%s", &username);
   printf("Enter your password: ");
   scanf("%s", &password);
   
   for (int i = 0; i < user_count; i++) {
      if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
         printf("Login successful!\n");
         return 1;
      }
   }
   
   printf("Invalid credentials. Please try again.\n");
   return 0;
}