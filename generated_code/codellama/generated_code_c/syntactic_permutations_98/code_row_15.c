#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <mysql/mysql.h>

    #define HOST "localhost"
    #define USER "root"
    #define PASSWORD ""
    #define DATABASE "registration_db"

    int main(){
        MYSQL *conn;
        conn = mysql_init(NULL);

        if(!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)){
            printf("Connection error: %s\n", mysql_error(conn));
            exit(1);
        }

        char *username;
        char password[32];

        printf("Enter your username:\n");
        scanf("%s", &username);
        getchar();

        printf("Enter your password:\n");
        gets(password);

        // Hash the password before inserting it into the database
        char *hashed_password = hash(password);

        char query[256];
        sprintf(query, "INSERT INTO users (username, password) VALUES ('%s', '%s');", username, hashed_password);

        if(mysql_query(conn, query)){
            printf("Insertion error: %s\n", mysql_error(conn));
            exit(1);
        }

        printf("Registration successful!");

        return 0;
    }