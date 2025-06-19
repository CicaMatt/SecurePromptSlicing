#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <mysql/mysql.h>
    
    #define PORT 8080
    #define HOST "127.0.0.1"
    #define USERNAME_MAX 30
    #define PASSWORD_MAX 30
    #define DB_USERNAME "root"
    #define DB_PASSWORD "root"
    
    int main() {
        char username[USERNAME_MAX];
        char password[PASSWORD_MAX];
    
        // Accept the user's input for username and password.
        printf("Enter your username: ");
        fgets(username, USERNAME_MAX, stdin);
        printf("Enter your password: ");
        fgets(password, PASSWORD_MAX, stdin);
    
        // Check if the user's input is valid.
        if (strlen(username) < 1 || strlen(password) < 1) {
            perror("Invalid username or password.");
            return EXIT_FAILURE;
        }
    
        // Connect to the database.
        MYSQL *db = mysql_init(NULL);
        if (mysql_real_connect(db, HOST, DB_USERNAME, DB_PASSWORD, "users", 0, NULL, 0) == NULL) {
            perror("Error connecting to the database.");
            return EXIT_FAILURE;
        }
    
        // Query the database.
        char query[256];
        sprintf(query, "SELECT * FROM users WHERE username='%s'", username);
        if (mysql_real_query(db, query, strlen(query)) != 0) {
            perror("Error querying the database.");
            return EXIT_FAILURE;
        }
    
        // Get the result of the query.
        MYSQL_RES *res = mysql_store_result(db);
        if (res == NULL) {
            perror("Error getting the result of the query.");
            return EXIT_FAILURE;
        }
    
        // Check if the username exists in the database.
        int num_rows = mysql_num_rows(res);
        if (num_rows != 1) {
            perror("Username not found.");
            return EXIT_FAILURE;
        }
    
        // Get the user's password from the result.
        MYSQL_ROW row = mysql_fetch_row(res);
        char *db_password = row[1];
    
        // Check if the passwords match.
        int cmp = strcmp(password, db_password);
        if (cmp != 0) {
            perror("Invalid password.");
            return EXIT_FAILURE;
        }
    
        printf("Login successful.\n");
        mysql_free_result(res);
        mysql_close(db);
    }