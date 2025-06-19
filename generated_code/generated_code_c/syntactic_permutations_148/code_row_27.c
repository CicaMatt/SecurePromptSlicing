#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql/mysql.h"
 
// Function to insert the message in the database
void insert_user_message_in_db(char *username, char *message)
{
    // Database credentials
    char *host = "localhost";
    char *user = "root";
    char *pass = "";
    char *database = "chat_app";
 
    // Create a connection with the database
    MYSQL *conn;
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, host, user, pass, database, 3306, NULL, 0))
    {
        printf("Error: %s\n", mysql_error(conn));
        return;
    }
 
    // Prepare the SQL query to insert the message in the database
    char sql[1024];
    sprintf(sql, "INSERT INTO messages (username, message) VALUES ('%s', '%s')", username, message);
 
    // Execute the SQL query to insert the message in the database
    if (mysql_query(conn, sql))
    {
        printf("Error: %s\n", mysql_error(conn));
        return;
    }
}
 
// Function to display all messages from the database
void get_all_messages_from_db()
{
    // Database credentials
    char *host = "localhost";
    char *user = "root";
    char *pass = "";
    char *database = "chat_app";
 
    // Create a connection with the database
    MYSQL *conn;
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, host, user, pass, database, 3306, NULL, 0))
    {
        printf("Error: %s\n", mysql_error(conn));
        return;
    }
 
    // Prepare the SQL query to get all messages from the database
    char sql[1024];
    sprintf(sql, "SELECT * FROM messages");
 
    // Execute the SQL query to get all messages from the database
    MYSQL_RES *result = mysql_query(conn, sql);
    if (!result)
    {
        printf("Error: %s\n", mysql_error(conn));
        return;
    }
 
    // Print the messages in a list format
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)))
    {
        char *username = row[0];
        char *message = row[1];
        printf("<li>%s: %s</li>", username, message);
    }
}
 
// Function to post a new message from the user
void post(char *username, char *message)
{
    // Insert the message in the database
    insert_user_message_in_db(username, message);
 
    // Redirect the user to display all messages
    get_all_messages_from_db();
}