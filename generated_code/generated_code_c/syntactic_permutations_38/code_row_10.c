// login.c
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>
 
// Structure to store user data
struct User {
    int id;
    char *username;
    char *password;
};
 
// Function to check the login credentials and redirect the user
void check_credentials(const struct User *user) {
    // Connect to database
    sqlite3 *db;
    if (sqlite3_open("login.db", &db)) {
        fprintf(stderr, "Failed to open database\n");
        exit(1);
    }
 
    // Define SQL query to select user data from the database
    char sql[200];
    sprintf(sql, "SELECT id FROM users WHERE username = '%s' AND password = '%s';", user->username, user->password);
 
    // Prepare SQL statement
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL)) {
        fprintf(stderr, "Failed to prepare SQL statement\n");
        exit(1);
    }
 
    // Execute SQL statement and check the result
    int ret = sqlite3_step(stmt);
    if (ret == SQLITE_ROW) {
        printf("Login successful!\n");
        fprintf(stderr, "User ID: %d\n", sqlite3_column_int(stmt, 0));
    } else {
        printf("Invalid username or password!\n");
    }
}
 
// Function to take input from the user and check credentials
void login() {
    // Structure to store user data
    struct User user;
 
    // Take input from the user
    printf("Enter your username: ");
    scanf("%s", &user.username);
    printf("Enter your password: ");
    scanf("%s", &user.password);
 
    // Check credentials and redirect the user
    check_credentials(&user);
}
 
int main() {
    login();
    return 0;
}