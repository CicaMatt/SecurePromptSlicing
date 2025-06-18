#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    // DB connection information
    char *host = "localhost";
    char *username = "root";
    char *password = "";
    char *db_name = "login_system";

    int main() {
        printf("Content-Type: text/html\n\n");

        // Connect to database
        MYSQL *conn;
        conn = mysql_init(NULL);

        if (!mysql_real_connect(conn, host, username, password, db_name, 0, NULL, 0)) {
            printf("Internal Server Error\n");
            exit(1);
        }

        // Get the username and password from the user
        char username[25];
        char password[25];

        scanf("%s %s", username, password);

        // Check if the username and password are in the database
        MYSQL_RES *result;
        MYSQL_ROW row;
        
        sprintf(query, "SELECT username, password FROM users WHERE username = '%s' AND password = '%s'", username, password);

        mysql_query(conn, query);
        result = mysql_store_result(conn);

        if (mysql_num_rows(result) == 1) {
            printf("Success\n");
        } else {
            printf("Error\n");
        }

        // Disconnect from the database
        mysql_free_result(result);
        mysql_close(conn);
        
        return 0;
    }