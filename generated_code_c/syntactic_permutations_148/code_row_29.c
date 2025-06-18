#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>
#define MAX_DATA 100
#define USERNAME_SIZE 32

// Connect to the database
MYSQL* connect() {
    // Create a MYSQL connection object
    MYSQL *conn = mysql_init(NULL);
 
    // Establish a connection to the database
    if (!mysql_real_connect(conn, "localhost", "username", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return NULL;
    }
 
    // Return the connection object
    return conn;
}
 
// Insert a message into the database
int insert_user_message_in_db(MYSQL *conn, const char *username, const char *message) {
    if (!mysql_query(conn, "INSERT INTO messages (username, message) VALUES ('%s', '%s')", username, message)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }
    return 0;
}
 
// Display the messages from the database
void display_messages(MYSQL *conn) {
    // Create a statement object
    MYSQL_STMT *stmt = mysql_stmt_init(conn);
 
    // Prepare a SQL query
    if (!mysql_stmt_prepare(stmt, "SELECT username, message FROM messages", strlen("SELECT username, message FROM messages"))) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }
 
    // Bind the statement object to a result set object
    MYSQL_RES *result = mysql_stmt_result_metadata(stmt);
 
    // Create an array of bindings for each column in the result set
    char **bind_data[MAX_DATA];
 
    // Iterate over each column in the result set and bind it to a variable
    int num_columns = mysql_num_fields(result);
    for (int i = 0; i < num_columns; i++) {
        MYSQL_FIELD *field = mysql_fetch_field_direct(result, i);
 
        // Allocate memory to store the data
        bind_data[i] = malloc(sizeof(char) * field->max_length + 1);
 
        // Bind the column to the variable
        mysql_stmt_bind_result(stmt, bind_data[i], field->max_length);
    }
 
    // Execute the statement and store the result set in a result set object
    if (!mysql_stmt_execute(stmt)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }
 
    // Iterate over each row in the result set and print the data
    while (mysql_stmt_fetch(stmt) != MYSQL_NO_DATA) {
        for (int i = 0; i < num_columns; i++) {
            printf("%s", bind_data[i]);
            if (i < num_columns - 1) {
                printf(", ");
            }
        }
        printf("\n");
    }
 
    // Free the memory allocated for each column
    for (int i = 0; i < num_columns; i++) {
        free(bind_data[i]);
    }
}
 
// The main function that starts the server
int main() {
    // Connect to the database
    MYSQL *conn = connect();
    if (conn == NULL) return 1;
 
    // Start the message display loop
    while (1) {
        char username[USERNAME_SIZE];
        printf("Username: ");
        scanf("%s", username);
        getchar(); // Consume newline character
 
        char message[MAX_DATA];
        printf("Message: ");
        fgets(message, MAX_DATA, stdin);
 
        if (insert_user_message_in_db(conn, username, message) == 1) return 1;
 
        display_messages(conn);
    }
 
    // Close the database connection
    mysql_close(conn);
 
    return 0;
}