#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// define structure for user data
struct UserData {
    char username[256];
    char password[256];
};

// function to generate salt
unsigned long generateSalt() {
    // return random number between 1000 and 9999
    return (rand() % 8999) + 1000;
}

// function to hash password with salt
void hashPassword(struct UserData* user, unsigned long salt) {
    // create temporary buffer for hashing
    char buffer[256];
    // copy username and salt to buffer
    strcpy(buffer, user->username);
    sprintf(buffer + strlen(user->username), "%lu", salt);
    // hash password using salt and store in user struct
    user->password = sha256(buffer);
}

// function to add user data to database
void addUserToDatabase(struct UserData* user) {
    // connect to database
    DatabaseConnection db = connectToDatabase("localhost", "my_database");
    // create query string
    char query[512];
    sprintf(query, "INSERT INTO users (username, password) VALUES ('%s', '%s')",
            user->username, user->password);
    // execute query and check for errors
    if (!executeQuery(db, query)) {
        printf("Error adding user to database: %s\n", getLastError());
    }
}

// function to prompt user for username and password
void promptForUsernameAndPassword(struct UserData* user) {
    // prompt user for username and password
    printf("Enter username: ");
    fgets(user->username, 256, stdin);
    printf("Enter password: ");
    fgets(user->password, 256, stdin);
}

int main() {
    // create struct for user data
    struct UserData user;
    // prompt user for username and password
    promptForUsernameAndPassword(&user);
    // generate salt
    unsigned long salt = generateSalt();
    // hash password with salt
    hashPassword(&user, salt);
    // add user data to database
    addUserToDatabase(&user);
    return 0;
}