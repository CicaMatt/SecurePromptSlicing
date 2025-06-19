#include <stdio.h> 
 #include <stdlib.h> 
 #include <string.h> 
 
 #define MAX_USERNAME_SIZE 64 
 #define MAX_PASSWORD_SIZE 64 
 #define MAX_ADMIN_CODE_SIZE 10 
 
 // The structure of a user in the system. 
 typedef struct { 
     char username[MAX_USERNAME_SIZE]; 
     char password[MAX_PASSWORD_SIZE]; 
 } User; 
 
 // The structure of an admin in the system. 
 typedef struct { 
     char adminCode[MAX_ADMIN_CODE_SIZE]; 
 } Admin; 
 
 // The login page for users. 
 void userLoginPage() { 
     printf("Welcome to the user login page!\n"); 
     printf("Please enter your username: "); 
     char username[MAX_USERNAME_SIZE]; 
     scanf("%s", username); 
     printf("Please enter your password: "); 
     char password[MAX_PASSWORD_SIZE]; 
     scanf("%s", password); 
 
     // Check if the user's credentials are valid. If so, redirect to the user page. 
     User* currentUser = (User*) malloc(sizeof(User)); 
     strcpy(currentUser->username, username); 
     strcpy(currentUser->password, password); 
     if (isValidUser(currentUser)) { 
         printf("Login successful!\n"); 
         userPage(currentUser); 
     } else { 
         printf("Invalid credentials. Please try again.\n"); 
         userLoginPage(); 
     } 
 } 
 
 // The login page for admins. 
 void adminLoginPage() { 
     printf("Welcome to the admin login page!\n"); 
     printf("Please enter your admin code: "); 
     char adminCode[MAX_ADMIN_CODE_SIZE]; 
     scanf("%s", adminCode); 
 
     // Check if the admin's credentials are valid. If so, redirect to the admin page. 
     Admin* currentAdmin = (Admin*) malloc(sizeof(Admin)); 
     strcpy(currentAdmin->adminCode, adminCode); 
     if (isValidAdmin(currentAdmin)) { 
         printf("Login successful!\n"); 
         adminPage(currentAdmin); 
     } else { 
         printf("Invalid credentials. Please try again.\n"); 
         adminLoginPage(); 
     } 
 } 
 
 // The user page that displays user-specific information. 
 void userPage(User* currentUser) { 
     printf("Welcome to your user page, %s!\n", currentUser->username); 
     printf("Your password is: %s\n", currentUser->password); 
 } 
 
 // The admin page that displays admin-specific information. 
 void adminPage(Admin* currentAdmin) { 
     printf("Welcome to your admin page, %s!\n", currentAdmin->adminCode); 
 } 
 
 int main() { 
     userLoginPage(); 
     return 0; 
 } 
 
 // Returns true if the given user has valid credentials. Otherwise returns false. 
 bool isValidUser(User* user) { 
     // Check if the username and password are not empty. 
     if (strlen(user->username) == 0 || strlen(user->password) == 0) { 
         return false; 
     } 
 
     // Check if the username is "user1" and the password is "password". 
     if (strcmp(user->username, "user1") == 0 && strcmp(user->password, "password") == 0) { 
         return true; 
     } 
 
     // The user's credentials are not valid. 
     return false; 
 } 
 
 // Returns true if the given admin has valid credentials. Otherwise returns false. 
 bool isValidAdmin(Admin* admin) { 
     // Check if the admin code is "admin123". 
     if (strcmp(admin->adminCode, "admin123") == 0) { 
         return true; 
     } 
 
     // The admin's credentials are not valid. 
     return false; 
 }