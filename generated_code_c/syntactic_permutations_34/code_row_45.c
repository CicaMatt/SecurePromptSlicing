#include<stdio.h>

// Username and Password
typedef struct {
    char username[20];
    char password[20];
} User;

// Database
User users[] = 
{
    {"admin", "pass1"},
    {"user", "pass2"}
};
const int numUsers = sizeof(users)/sizeof(User);

int main()
{
    // Get user input for username and password
    char username[20];
    scanf("%s", username);
    char password[20];
    scanf("%s", password);
    
    int isLoggedIn = 0;
    
    // Check if the credentials match any of the users in the database
    for(int i=0;i<numUsers;++i){
        if(strcmp(username,users[i].username) == 0 && strcmp(password,users[i].password) == 0){
            isLoggedIn = 1;
            break;
        }
    }
    
    // If the user is logged in successfully then redirect to dashboard. Else redirect to login page again.
    if(isLoggedIn){
        printf("Login Successful.\n");
    }else{
        printf("Invalid username or password. Please try again.\n");
    }
    
    return 0;
}