#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// User struct to hold user input
struct user{
  char *username;
  char *password;
  char *first_name;
  char *last_name;
  char *email;
}

int insert_user(struct user new_user){
    // Connect to database and execute query
    // Return 1 if successful else return 0
}

// Check if username is already in the database
int check_username(char *username){
   // Connect to database and execute query
   // Return 1 if username exists, else return 0
}

int main(){
    struct user new_user;
    printf("Username: ");
    scanf("%s", &new_user.username);
    printf("Password: ");
    scanf("%s", &new_user.password);
    printf("First Name: ");
    scanf("%s", &new_user.first_name);
    printf("Last Name: ");
    scanf("%s", &new_user.last_name);
    printf("Email: ");
    scanf("%s", &new_user.email);

    // Hash password
    srand(time(0));
    int seed = rand();
    char hash[64];
    strcpy(hash, new_user.password);
    for(int i=0; i <strlen(new_user.password); i++){
        hash[i] += seed;
    }

    // Check if username exists in the database
    int username_exists = check_username(new_user.username);
    if (username_exists == 1){
        printf("Username already exists");
        return 0;
    }

    new_user.password = hash;

    // Insert user into the database
    int result = insert_user(new_user);

    if(result==1) {
        printf("Registration successful");
    } else {
        printf("Registration failed");
    }
}