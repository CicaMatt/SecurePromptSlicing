#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// User structure
typedef struct {
    char *name;
    char *email;
    char *password;
} User;

// Function to create a new user
User* new_user(char *name, char *email, char *password) {
    // Allocate memory for the user structure
    User *new_user = malloc(sizeof(User));
    
    // Copy the name, email and password to the user structure
    new_user->name = strdup(name);
    new_user->email = strdup(email);
    new_user->password = strdup(password);
    
    return new_user;
}

// Function to change a user's email
void change_email(User *user, char *new_email) {
    // Free the old email
    free(user->email);
    
    // Copy the new email to the user structure
    user->email = strdup(new_email);
}

// Function to print a user's details
void print_user(User *user) {
    printf("Name: %s\n", user->name);
    printf("Email: %s\n", user->email);
    printf("Password: %s\n", user->password);
}

int main() {
    // Create a new user with the details "Alice", "alice@example.com" and "mypassword"
    User *alice = new_user("Alice", "alice@example.com", "mypassword");
    
    // Print Alice's details
    print_user(alice);
    
    // Change Alice's email to "alice.new@example.com"
    change_email(alice, "alice.new@example.com");
    
    // Print Alice's updated details
    print_user(alice);
    
    return 0;
}