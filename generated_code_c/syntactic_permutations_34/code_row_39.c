#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Struct for user details
struct UserDetails{
    char username[100];
    char password[100];
};

// Function to check if user is authenticated
int isAuthenticated(char* username, char* password){
    // Database containing username and passwords
    struct UserDetails users[] = {{"admin", "password"}, {"user", "pass"}};
    int num_users = sizeof(users)/sizeof(struct UserDetails);

    for(int i=0;i<num_users;i++){
        if(strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0){
            return 1;
        }
    }
    // If loop above doesn't execute then user is not authenticated
    return 0;
}

int main(){
    char username[100];
    char password[100];

    printf("Enter your username: ");
    fgets(username, 100, stdin);
    printf("Enter your password: ");
    fgets(password, 100, stdin);

    if(isAuthenticated(username, password)){
        // Redirect to dashboard page
        printf("Login Successful. Redirecting to Dashboard...\n");
    }else{
        // Redirect back to login page
        printf("Login Failed. Incorrect username or password.\n");
    }
    return 0;
}