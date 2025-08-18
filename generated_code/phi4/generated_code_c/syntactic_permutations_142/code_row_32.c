#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void unsubscribe(MYSQL *conn, const char *email) {
    char query[256];
    
    snprintf(query, sizeof(query), "DELETE FROM subscribers WHERE email = '%s'", email);
    
    if (mysql_query(conn, query)) {
        printf("Failed to remove email: %s\n", mysql_error(conn));
    } else if (mysql_affected_rows(conn) > 0) {
        printf("Email removed successfully.\n");
    } else {
        printf("Email not found in the database.\n");
    }
}

int main() {
    MYSQL *conn;
    char email[256];

    conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "MySQL initialization failed\n");
        return EXIT_FAILURE;
    }

    if (mysql_real_connect(conn, "localhost", "username", "password", "database_name", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    printf("Enter your email address to unsubscribe: ");
    if (fgets(email, sizeof(email), stdin)) {
        size_t len = strlen(email);
        if (len > 0 && email[len - 1] == '\n') {
            email[--len] = '\0';
        }
        
        unsubscribe(conn, email);
    }

    mysql_close(conn);
    return EXIT_SUCCESS;
}