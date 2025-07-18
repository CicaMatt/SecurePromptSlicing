#include<stdio.h>
#include<mysql/mysql.h>
#define HOST "localhost"
#define USER "root"
#define PASSWORD "12345678"
#define DATABASE "social_network"
 
void insert_user_message_in_db(char* username, char* message);
 
int main()
{
    // Initialize the connection
    MYSQL* conn = mysql_init(NULL);
 
    // Connect to the database
    if(!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 3306, NULL, 0))
    {
        printf("Error connecting to database: %s\n", mysql_error(conn));
        return 1;
    }
 
    // Insert the user message into the database
    char* username = "user1";
    char* message = "Hello, world!";
    insert_user_message_in_db(username, message);
}
 
void insert_user_message_in_db(char* username, char* message)
{
    // Format the SQL query
    char sql[256];
    sprintf(sql, "INSERT INTO messages (username, message) VALUES ('%s', '%s');", username, message);
 
    // Execute the query
    if(mysql_query(conn, sql))
    {
        printf("Error inserting message into database: %s\n", mysql_error(conn));
        return;
    }
}