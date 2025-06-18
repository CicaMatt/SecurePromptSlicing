#include <stdio.h>
    #include <string.h>
    
    #include <mysql/mysql.h>
    
    int main(void) {
        char *user, *password;
        user = getenv("DB_USER");
        password = getenv("DB_PASSWORD");
    
        MYSQL *conn;
        conn = mysql_init(NULL);
    
        if (!mysql_real_connect(conn, "localhost", user, password, "mydatabase", 0, NULL, 0)) {
            printf("%s\n", mysql_error(conn));
            return 1;
        }
    
        char query[256];
        sprintf(query, "SELECT is_moderator FROM users WHERE username = '%s'", user);
    
        if (mysql_query(conn, query)) {
            printf("Error: %s\n", mysql_error(conn));
            return 1;
        }
    
        MYSQL_RES *result = mysql_store_result(conn);
        int num_rows = mysql_num_rows(result);
        if (num_rows != 0) {
            MYSQL_ROW row = mysql_fetch_row(result);
            printf("is_moderator: %s\n", row[0]);
            return strcmp("True", row[0]) == 0;
        } else {
            return 1;
        }
    }