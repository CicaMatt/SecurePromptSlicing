#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

// Function declaration
int checkIfModerator(sqlite3 *db, const char *username);

// Web server function to handle requests (simulated)
void handleWebRequest(const char *route) {
    sqlite3 *db;
    
    // Open the database connection
    if (sqlite3_open("users.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    // Check if the user is a moderator based on the route parameter
    const char *username = strtok((char *)route + 1, "/"); // Simulated extraction of username from route

    int isModerator = checkIfModerator(db, username);

    // Close the database connection
    sqlite3_close(db);

    // Return the result (simulated)
    printf("User '%s' is %sa moderator.\n", username, isModerator ? "" : "not ");

}

// Function to check if a user is a moderator in the database
int checkIfModerator(sqlite3 *db, const char *username) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT 1 FROM users WHERE username = ? AND is_moderator = 1 LIMIT 1;";
    
    // Prepare SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL)) {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Bind the username parameter to the SQL statement
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

    // Execute the query and check for results
    int result = sqlite3_step(stmt) == SQLITE_ROW;

    // Finalize the statement
    sqlite3_finalize(stmt);

    return result;
}

// Main function to simulate a web server request
int main() {
    // Simulate a route call like "/user/johndoe"
    handleWebRequest("/user/johndoe");
    return 0;
}