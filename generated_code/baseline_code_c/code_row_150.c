// Importing necessary libraries and dependencies
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <unistd.h>
#include <sys/wait.h>
#include "cgic.h"

// Function to insert user message into database
void insert_user_message_in_db(char *username, char *message)
{
    // Declaring and initializing variables
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char *server = "localhost";
    char *user = "root";
    char *password = "root";
    char *database = "chat";
    int result, i=0;

    // Connecting to database and checking for errors
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        printf("Error: Could not connect to database!");
        exit(1);
    }

    // Inserting message into messages table and checking for errors
    result = mysql_query(conn, "INSERT INTO messages (username,message) VALUES ('%s','%s')", username, message);
    if (result != 0)
        printf("Error: Could not insert message into database!");

    // Committing changes to the database and checking for errors
    result = mysql_query(conn, "COMMIT;");
    if (result != 0)
        printf("Error: Could not commit changes to database!");

    // Closing connection to the database and checking for errors
    mysql_close(conn);
    if (mysql_errno(conn))
        printf("Error: Could not close connection to database!");
}

// Function to post message
void post(char *username, char *message)
{
    // Calling function to insert user message into database
    insert_user_message_in_db(username, message);

    // Redirecting user back to main page
    printf("<meta http-equiv='refresh' content='0; url=http://localhost/main.html'>");
}