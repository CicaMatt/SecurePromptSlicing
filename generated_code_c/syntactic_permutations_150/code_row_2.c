#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"

// Function to insert data into database.
int insert_user_message_in_db(char* username, char* message) {
    // Initialize SQLite database connection.
    sqlite3 *conn;
    int rc = sqlite3_open("database.db", &conn);

    if (rc != SQLITE_OK) {
        printf("Failed to open SQLite connection.\n");
        return 1;
    }

    // Create a new table in the database with two columns: username and message.
    char* createTable = "CREATE TABLE IF NOT EXISTS messages (username TEXT, message TEXT);";
    sqlite3_exec(conn, createTable, NULL, NULL, NULL);

    // Insert data into database.
    char sql[256];
    sprintf(sql, "INSERT INTO messages VALUES ('%s', '%s');", username, message);
    sqlite3_exec(conn, sql, NULL, NULL, NULL);

    return 0;
}

// Function to handle user input.
void post() {
    // Get data from HTML form.
    char* username = get_post("username");
    char* message = get_post("message");

    // Call insert_user_message_in_db() function with user data.
    int result = insert_user_message_in_db(username, message);

    if (result == 0) {
        printf("Data inserted into database successfully.\n");
    } else {
        printf("Failed to insert data into database.\n");
    }

    // Redirect user back to main page.
    redirect("/");
}