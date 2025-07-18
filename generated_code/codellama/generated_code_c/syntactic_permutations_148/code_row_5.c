// Import necessary libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>

// Define variables and functions
char *username;
char *message;
int insert_user_message_in_db(char *username, char *message);
void display_messages();

// Main function
int main()
{
    // Get username and message from the request
    printf("Enter your username: ");
    scanf("%s", &username);
    printf("Enter your message: ");
    scanf("%s", &message);

    // Call insert_user_message_in_db() function to insert the message in the database
    int result = insert_user_message_in_db(username, message);

    // Redirect the user to the main page
    printf("You are now redirected to the main page.\n");
    system("main.c"); // Replace this with the correct command to execute the main.c file

    return 0;
}

// insert_user_message_in_db() function definition
int insert_user_message_in_db(char *username, char *message)
{
    // Create a database connection
    sqlite3 *db;
    int rc = sqlite3_open("messages.db", &db);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to open the database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Create a SQL statement to insert the message into the database
    char sql[256];
    sprintf(sql, "INSERT INTO messages (username, message) VALUES ('%s', '%s')", username, message);

    // Execute the SQL statement
    rc = sqlite3_exec(db, sql, NULL, 0, NULL);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to execute the SQL statement: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Close the database connection
    sqlite3_close(db);

    return 0;
}

// display_messages() function definition
void display_messages()
{
    // Create a database connection
    sqlite3 *db;
    int rc = sqlite3_open("messages.db", &db);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to open the database: %s\n", sqlite3_errmsg(db));
        return;
    }

    // Create a SQL statement to retrieve all messages from the database
    char sql[256];
    sprintf(sql, "SELECT * FROM messages");

    // Execute the SQL statement and display all messages
    rc = sqlite3_exec(db, sql, display_messages_callback, NULL, NULL);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to execute the SQL statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    // Close the database connection
    sqlite3_close(db);
}

// display_messages_callback() function definition
int display_messages_callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    for (int i = 0; i < argc; i++)
    {
        printf("%s: %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}