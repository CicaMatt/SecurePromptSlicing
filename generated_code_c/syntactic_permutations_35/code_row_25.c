#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <mysql/mysql.h>
    #include <stdbool.h>

    typedef struct user_data {
        char username[50];
        char password[50];
    } user_data;

    int main() {
        // Create the database connection
        MYSQL *conn = mysql_init(NULL);
        if (conn == NULL) {
            printf("Connection to database failed\n");
            exit(1);
        }

        // Connect to the database
        conn = mysql_real_connect(conn, "localhost", "root", "password", "database", 3306, NULL, 0);
        if (conn == NULL) {
            printf("Connection to database failed\n");
            exit(1);
        }

        // Check the form data and validate the user
        char username[50];
        char password[50];
        int is_user = 0;
        while (1) {
            printf("Enter your username: ");
            scanf("%s", username);
            printf("Enter your password: ");
            scanf("%s", password);

            // Create the SQL query to check if the user exists in the database
            char sql[200];
            sprintf(sql, "SELECT * FROM users WHERE username='%s' AND password='%s';", username, password);

            // Execute the query and get the result
            MYSQL_RES *res = mysql_query(conn, sql);
            if (mysql_num_rows(res) == 1) {
                is_user = 1;
                break;
            }
        }

        // Check if the user exists in the database and redirect to the home page or login page
        if (is_user) {
            printf("User found in the database. Redirecting to home page...\n");
        } else {
            printf("User not found in the database. Redirecting to login page...\n");
        }

        // Close the database connection
        mysql_close(conn);
        return 0;
    }