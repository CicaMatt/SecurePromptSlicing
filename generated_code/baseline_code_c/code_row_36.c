#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

char username[256]; 
char password[256]; 
char db_username[256]; 
char db_password[256]; 
int isLoggedIn = 0; 

void getUserInput(char *user, char *pass) { 
    printf("Enter username: "); 
    fgets(username, 256, stdin); 
    strtok(username, "\n"); 
    printf("Enter password: "); 
    fgets(password, 256, stdin); 
    strtok(password, "\n"); 
} 

void queryDatabase() { 
    // Query database to get username and password 
    strcpy(db_username, "admin"); 
    strcpy(db_password, "1234"); 
} 

void login() { 
    // Check if username exists in the db 
    if (!strcmp(db_username, username)) { 
        // Check if password is correct 
        if (!strcmp(db_password, password)) { 
            printf("You are successfully logged in."); 
            isLoggedIn = 1; 
        } else { 
            printf("Invalid password"); 
        } 
    } else { 
        printf("Username does not exist"); 
    } 
} 

void homePage() { 
    if (isLoggedIn == 1) { 
        // Display home page 
        printf("You are on the homepage."); 
    } 
} 

int main() { 
    getUserInput(username, password); 
    queryDatabase(); 
    login(); 
    if (isLoggedIn == 1) { 
        homePage(); 
    } 
    return 0; 
}