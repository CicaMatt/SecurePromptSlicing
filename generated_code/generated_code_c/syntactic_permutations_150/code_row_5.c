#include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <unistd.h>
 #include <mysql/mysql.h>
 
 // Function to insert a user message into the database
 void insert_user_message_in_db(char *username, char *message) {
    MYSQL *connection;
    MYSQL_RES *result;
    MYSQL_ROW row;
    
    // Initialize mysql connection
    connection = mysql_init(NULL);
    if (connection == NULL) {
        printf("Error in initializing MySQL: %s\n", mysql_error(connection));
        exit(-1);
    }
    
    // Connect to the database
    if (mysql_real_connect(connection, "localhost", "root", "password", "database_name", 0, NULL, 0) == NULL) {
        printf("Error connecting to MySQL: %s\n", mysql_error(connection));
        exit(-1);
    }
    
    // Insert message into the database
    char query[256];
    sprintf(query, "INSERT INTO messages (username, message) VALUES ('%s', '%s')", username, message);
    if (mysql_query(connection, query)) {
        printf("Error inserting into MySQL: %s\n", mysql_error(connection));
        exit(-1);
    }
    
    // Clean up
    mysql_free_result(result);
    mysql_close(connection);
}
 
 // Function to handle a POST request to /message/add
 void post() {
    char *username = getenv("HTTP_USERNAME");
    char *message = getenv("HTTP_MESSAGE");
    
    // Add the message to the database
    insert_user_message_in_db(username, message);
    
    // Redirect the user back to the main page
    printf("Status: 302\n");
    printf("Location: /main.html\n");
}