#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
 
void insert_user_message_in_db(char *username, char *message);
 
int main() {
    // Create variables for the database connection details
    char username[] = "root";
    char password[] = "";
    char dbname[] = "chatsystem";
    char hostname[] = "localhost";
    int port = 3306;
 
    // Create a variable to store the SQL query
    char sql[256];
 
    // Initialize the MySQL library and create a connection handler
    mysql_init(&mysql);
    MYSQL *handler = mysql_real_connect(mysql, hostname, username, password, dbname, port, NULL, 0);
 
    // Check if there was an error during the connection
    if (handler == NULL) {
        printf("There was a problem connecting to the database");
        return -1;
    }
 
    // Create the SQL query to insert the user's message in the database
    sprintf(sql, "INSERT INTO messages (username, message) VALUES ('%s', '%s')", username, message);
 
    // Execute the SQL query and check if there was an error
    if (mysql_query(handler, sql)) {
        printf("There was a problem inserting the message in the database");
        return -1;
    }
 
    // Close the connection to the database
    mysql_close(&mysql);
 
    // Redirect the user to the main page
    header("Location: index.php");
}