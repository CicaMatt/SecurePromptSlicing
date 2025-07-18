#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "openssl/sha.h"

//defining structures for user details
typedef struct User {
    char username[100];
    char password[100];
    char first_name[100];
    char last_name[100];
    char email[100];
}User;

//defining structures for user database
typedef struct User_Database {
    User *users;
    int size;
}User_Database;

//function to generate hashed password
void createHash(char password[100]){
    unsigned char result[SHA256_DIGEST_LENGTH];
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, password, strlen(password));
    SHA256_Final(result, &ctx);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(password+2*i, "%02x", result[i]);
    }
}
//function to check if username exists in database
int userExists(User_Database database, char username[100]){
    for (int i = 0; i < database.size; ++i) {
        if (strcmp(database.users[i].username, username) == 0){
            return 1;
        }
    }
    return 0;
}
//function to insert user into database
void addUser(User_Database *database, User user){
    int i = database->size;
    database->size++;
    database->users = (User*)realloc(database->users, sizeof(User)*database->size);
    database->users[i] = user;
}
//function to print the user details from the database
void printUsers(User_Database database){
    for (int i = 0; i < database.size; ++i) {
        User user = database.users[i];
        printf("username: %s\n", user.username);
        printf("password: %s\n", user.password);
        printf("first name: %s\n", user.first_name);
        printf("last name: %s\n", user.last_name);
        printf("email: %s\n", user.email);
    }
}
//function to register a new user
void registerUser(char username[100], char password[100], char first_name[100], char last_name[100], char email[100]){
    User user = {username, password, first_name, last_name, email};
    createHash(user.password);
    if (userExists(database, username) == 1){
        printf("Username already exists");
    }
    else {
        addUser(&database, user);
        printUsers(database);
    }
}
int main(){
    char username[100];
    char password[100];
    char first_name[100];
    char last_name[100];
    char email[100];
    
    User_Database database = {NULL, 0};
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
    printf("Enter first name: ");
    scanf("%s", first_name);
    printf("Enter last name: ");
    scanf("%s", last_name);
    printf("Enter email: ");
    scanf("%s", email);

    registerUser(username, password, first_name, last_name, email);
}