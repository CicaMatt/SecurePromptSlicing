#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <mysql/mysql.h>

    struct database {
        char host[50];
        char user[50];
        char password[50];
        char db[50];
    };

    void login(char *username, char *password) {
        MYSQL *conn;
        char query[200] = "SELECT username FROM users WHERE username='";
        strcat(query, username);
        strcat(query, "'");

        conn = mysql_init(NULL);

        if (!mysql_real_connect(conn, host, user, password, db, 0, NULL, 0)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }

        MYSQL_RES *res = mysql_query(conn, query);
        if (res) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }

        MYSQL_ROW row = mysql_fetch_row(res);
        if (!row) {
            printf("User not found\n");
            return;
        }

        char *hashed_password = row[0];
        if (strcmp(hashed_password, password)) {
            printf("Incorrect password\n");
            return;
        }

        printf("Login successful!\n");
    }

    void get_login_info() {
        char username[50], password[50];
        printf("Username: ");
        scanf("%s", username);
        printf("Password: ");
        scanf("%s", password);
        login(username, password);
    }

    int main() {
        get_login_info();
        return 0;
    }