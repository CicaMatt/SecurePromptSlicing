#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <mysql/mysql.h>  //include mysql header file

    int main()
    {
        char email[50];
        printf("Enter your email address: ");
        scanf("%s", &email);

        MYSQL *conn;  //the connection
        MYSQL_RES *res;  //the results
        MYSQL_ROW row;

        char *server = "localhost";
        char *user = "root";
        char *password = "yourpassword";
        char *database = "mydb";

        //connect to the database
        conn = mysql_init(NULL);

        if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
            printf("Conection error: %s\n", mysql_error(conn));
            exit(1);
        }

        char query[256];
        sprintf(query, "SELECT * FROM users WHERE email = '%s' LIMIT 1", email);

        //execute the query
        if (mysql_query(conn, query)) {
            printf("MySQL error: %s\n", mysql_error(conn));
            exit(1);
        }

        res = mysql_store_result(conn);

        //if the email address is in the database, delete it and tell the user that they are unsubscribed.
        if (mysql_num_rows(res) == 1) {
            sprintf(query, "DELETE FROM users WHERE email = '%s'", email);

            //execute the query
            if (mysql_query(conn, query)) {
                printf("MySQL error: %s\n", mysql_error(conn));
                exit(1);
            }

            printf("You have been unsubscribed.\n");
        } else {
            printf("Your email address is not in our database.\n");
        }

        //close the connection
        mysql_free_result(res);
        mysql_close(conn);
    }