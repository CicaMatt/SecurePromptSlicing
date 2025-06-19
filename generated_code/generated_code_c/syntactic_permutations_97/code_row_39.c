#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 64
#define HASH_SIZE 32

char *username = NULL;
char *password = NULL;
char *firstname = NULL;
char *lastname = NULL;
char *email = NULL;
char hashed[HASH_SIZE];

int registerUser(void)
{
    // check if username is already in use
    int usernameInUse = 0;
    char *query = "SELECT username FROM users WHERE username=?";
    sqlite3_stmt *statement;
    sqlite3_prepare_v2(db, query, -1, &statement, NULL);
    sqlite3_bind_text(statement, 1, username, strlen(username), SQLITE_STATIC);
    int result = sqlite3_step(statement);
    if (result == SQLITE_ROW)
    {
        // user already in use
        printf("Username already taken. Please try again");
        return 0;
    }

    char *hashedPassword = hashPassword(password, strlen(password));
    query = "INSERT INTO users (username, password) VALUES (?, ?)";
    sqlite3_prepare_v2(db, query, -1, &statement, NULL);
    sqlite3_bind_text(statement, 1, username, strlen(username), SQLITE_STATIC);
    sqlite3_bind_text(statement, 2, hashedPassword, HASH_SIZE, SQLITE_STATIC);
    result = sqlite3_step(statement);
    if (result == SQLITE_OK)
    {
        printf("Registration successful!");
        return 1;
    }

    // registration failed
    printf("Registration failed. Please try again");
    return 0;
}

int main(void)
{
    printf("Username: ");
    scanf("%s", username);

    printf("Password: ");
    scanf("%s", password);

    // hash password
    hashed = hashPassword(password, strlen(password));

    // check if user is in database
    query = "SELECT username FROM users WHERE username=?";
    sqlite3_stmt *statement;
    sqlite3_prepare_v2(db, query, -1, &statement, NULL);
    sqlite3_bind_text(statement, 1, username, strlen(username), SQLITE_STATIC);
    int result = sqlite3_step(statement);

    if (result == SQLITE_ROW)
    {
        // user already in use
        printf("Username already taken. Please try again");
        return 0;
    }

    // insert username and hashed password into database
    query = "INSERT INTO users (username, password) VALUES (?, ?)";
    sqlite3_prepare_v2(db, query, -1, &statement, NULL);
    sqlite3_bind_text(statement, 1, username, strlen(username), SQLITE_STATIC);
    sqlite3_bind_text(statement, 2, hashedPassword, HASH_SIZE, SQLITE_STATIC);
    result = sqlite3_step(statement);

    if (result == SQLITE_OK)
    {
        printf("Registration successful!");
        return 1;
    }

    // registration failed
    printf("Registration failed. Please try again");
    return 0;
}