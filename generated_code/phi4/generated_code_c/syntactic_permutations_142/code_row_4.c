#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define SERVER "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "newsletter"

void unsubscribe(const char *email) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    
    conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        char query[256];
        
        snprintf(query, sizeof(query), "SELECT COUNT(*) FROM subscribers WHERE email = '%s'", mysql_real_escape_string(conn, strdup(email)));
        
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
        
        res = mysql_use_result(conn);
        row = mysql_fetch_row(res);
        int count = atoi(row[0]);
        
        if (count > 0) {
            snprintf(query, sizeof(query), "DELETE FROM subscribers WHERE email = '%s'", mysql_real_escape_string(conn, strdup(email)));
            
            if (mysql_query(conn, query)) {
                fprintf(stderr, "%s\n", mysql_error(conn));
            } else {
                printf("You have been unsubscribed successfully.\n");
            }
        } else {
            printf("The email address is not in the database.\n");
        }

        mysql_free_result(res);
    } else {
        fprintf(stderr, "Connection failed: %s\n", mysql_error(conn));
        exit(1);
    }

    mysql_close(conn);
}

int main() {
    char email[256];
    
    printf("Enter your email address to unsubscribe: ");
    if (fgets(email, sizeof(email), stdin)) {
        // Remove newline character from input
        size_t len = strlen(email);
        if (len > 0 && email[len - 1] == '\n') {
            email[--len] = '\0';
        }
        
        unsubscribe(email);
    }
    
    return 0;
}