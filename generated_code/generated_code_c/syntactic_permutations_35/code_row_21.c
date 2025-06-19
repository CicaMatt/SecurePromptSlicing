#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <netdb.h>
    #include <mysql.h>
    #include <errno.h>
    #include "login.html"

    int login(char *username, char *password) {
        MYSQL *con = mysql_init(NULL);
        
        if (con == NULL) {
            printf("Error %u: %s\n", mysql_errno(con), mysql_error(con));
            exit(1);
        }

        if (mysql_real_connect(con, "localhost", "root", "password", "mydatabase", 3306, NULL, 0) == NULL) {
            printf("Error %u: %s\n", mysql_errno(con), mysql_error(con));
            exit(1);
        }

        char query[256];
        sprintf(query, "SELECT * FROM users WHERE username='%s' AND password='%s';", username, password);

        if (mysql_real_query(con, query, strlen(query)) != 0) {
            printf("Error %u: %s\n", mysql_errno(con), mysql_error(con));
            exit(1);
        }

        MYSQL_RES *result = mysql_store_result(con);
        
        if (mysql_num_rows(result) == 0) {
            return 0;
        } else {
            return 1;
        }
    }

    int main() {
        char username[256];
        char password[256];
        
        printf("Username: ");
        scanf("%s", username);
        printf("Password: ");
        scanf("%s", password);

        if (login(username, password) == 1) {
            printf("Login success! Redirecting to home page...\n");
            sleep(3);
            return 0;
        } else {
            printf("Login failed! Redirecting to login page...\n");
            sleep(3);
            return -1;
        }
    }