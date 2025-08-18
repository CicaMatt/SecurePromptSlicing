#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mysql/mysql.h>  // Make sure MySQL client library is installed

void unsubscribe(const char *email) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    
    if (!conn) {
        fprintf(stderr, "MySQL initialization failed\n");
        return;
    }

    conn = mysql_real_connect(conn, "localhost", "username", "password", "database_name", 0, NULL, 0);

    if (conn == NULL) {
        fprintf(stderr, "Connection error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT email FROM subscribers WHERE email = '%s'", email);

    int ret = mysql_query(conn, query);

    if (ret != 0) {
        fprintf(stderr, "Query error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    res = mysql_use_result(conn);

    if ((row = mysql_fetch_row(res)) == NULL) {
        printf("Email address not found in the database.\n");
    } else {
        snprintf(query, sizeof(query), "DELETE FROM subscribers WHERE email = '%s'", email);
        
        ret = mysql_query(conn, query);

        if (ret != 0) {
            fprintf(stderr, "Delete error: %s\n", mysql_error(conn));
        } else {
            printf("Email address successfully removed from the database.\n");
        }
    }

    mysql_free_result(res);
    mysql_close(conn);
}

int main() {
    char email[256];
    
    printf("Enter your email to unsubscribe: ");
    if (fgets(email, sizeof(email), stdin) != NULL) {
        // Remove newline character
        size_t len = strlen(email);
        if (len > 0 && email[len - 1] == '\n') {
            email[len - 1] = '\0';
        }
        
        unsubscribe(email);
    }

    return 0;
}


Make sure to replace `"username"`, `"password"`, and `"database_name"` with your actual database credentials. Also, ensure that the MySQL client library is installed and linked correctly during compilation using `-lmysqlclient`.