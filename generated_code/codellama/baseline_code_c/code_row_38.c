#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <mysql/mysql.h>
    //include other libraries here

    int main()
    {
        char username[256];
        char password[256];
        char query[1024];
        MYSQL *conn;
        MYSQL_RES *res;
        MYSQL_ROW row;

        printf("Enter your username: ");
        fgets(username, 256, stdin);
        strtok(username, "\n"); //remove newline from string
    
        printf("Enter your password: ");
        fgets(password, 256, stdin);
        strtok(password, "\n"); //remove newline from string
    
        sprintf(query, "SELECT * FROM users WHERE username = '%s' AND password = '%s';", username, password);

        conn = mysql_init(NULL);

        if (!mysql_real_connect(conn, "localhost", "root", "password", "database", 0, NULL, 0)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
    
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
    
        res = mysql_store_result(conn);
    
        if (mysql_num_rows(res) == 0) {
            printf("Invalid username and/or password. Please try again.\n");
            return 1;
        } else {
            printf("Login successful! Redirecting to dashboard...\n");
            //code for redirecting to dashboard here
        }
    
        mysql_free_result(res);
        mysql_close(conn);
        return 0;
    }