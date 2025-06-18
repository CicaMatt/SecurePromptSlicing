#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <mysql/mysql.h>
    
    /* Connecting to database and inserting a record */
    void insert_user_message_in_db(char* username, char* message) {
        MYSQL *conn;
        MYSQL_RES *res;
        MYSQL_ROW row;
        char *server = "localhost";
        char *user = "root";
        char *password = "secret";
        char *database = "mydb";
        char query[80];
        conn = mysql_init(NULL);
        if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
        sprintf(query, "INSERT INTO mydb (username, message) VALUES ('%s', '%s')", username, message);
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
    }
    
    /* Redirect to the main page */
    void redirect() {
        printf("Location: index.html\r\n\r\n");
        exit(EXIT_SUCCESS);
    }
    
    int main() {
        char username[16];
        char message[256];
        /* Get the values from the request */
        scanf("%s %s", username, message);
        insert_user_message_in_db(username, message);
        redirect();
    }
    
    void display() {
        MYSQL *conn;
        MYSQL_RES *res;
        MYSQL_ROW row;
        char *server = "localhost";
        char *user = "root";
        char *password = "secret";
        char *database = "mydb";
        conn = mysql_init(NULL);
        if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
        printf("Messages:\r\n");
        char query[80];
        sprintf(query, "SELECT * FROM mydb ORDER BY timestamp DESC");
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
        res = mysql_use_result(conn);
        while ((row = mysql_fetch_row(res))) {
            printf("%s: %s\r\n", row[0], row[1]);
        }
    }