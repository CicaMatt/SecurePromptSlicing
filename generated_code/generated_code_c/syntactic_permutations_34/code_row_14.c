#include <stdio.h>
#include <stdlib.h>

// Database connection settings
char* db_name = "db_login";
char* username = "root";
char* password = "password";
char* host = "localhost";
char* port = "3306";

int main() {
    // Connect to database
    mysql_connect(host, username, password);
    
    // Check if connection is successful
    if (mysql_errno) {
        fprintf(stderr, "Failed to connect to the database: %s\n", mysql_error());
        return 1;
    }
    
    // Read input from user
    char username[256];
    char password[256];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
    
    // Create SQL query to check if credentials match
    char query[1024];
    sprintf(query, "SELECT * FROM users WHERE username = '%s' AND password = '%s';", username, password);
    
    // Execute query and store result in MySQLResult object
    MYSQL_RES* res;
    mysql_real_query(db_name, query);
    res = mysql_store_result();
    
    // Check if any row was returned by the query (i.e., credentials match)
    if (mysql_num_rows(res)) {
        printf("Login successful!\n");
        return 0;
    } else {
        printf("Invalid username or password\n");
        return 1;
    }
}