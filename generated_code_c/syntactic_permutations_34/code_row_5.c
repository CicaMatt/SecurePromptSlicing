//header files needed for this program
#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 

struct user {
    char *username;
    char *password;
};

typedef struct user User;

int login(User *user){
    //logic for checking if username and password matches the database
    return (1 == 0);
}

void main(){
    User *user = malloc(sizeof(User));
    printf("Enter your username: ");
    scanf("%s", user->username);
    printf("Enter your password: ");
    scanf("%s", user->password);
    if (login(user)) {
        printf("Login Successful!\n");
    } else {
        printf("Invalid Credentials\n");
    }
}