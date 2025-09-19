#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MAX_PATH 256
#define SQL_QUERY "INSERT INTO files (filepath) VALUES ('%s')"

void upload_pdf(const char *filename) {
    MYSQL *conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "MySQL initialization failed\n");
        exit(1);
    }

    if (mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    char filepath[MAX_PATH];
    snprintf(filepath, sizeof(filepath), "uploads/%s", filename);

    FILE *file = fopen(filepath, "wb");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", filepath);
        mysql_close(conn);
        exit(1);
    }

    // Assume the PDF content is read and written here
    fclose(file);

    char query[MAX_PATH];
    snprintf(query, sizeof(query), SQL_QUERY, filepath);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "MySQL query failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    mysql_close(conn);
}

int main() {
    // Example usage
    upload_pdf("example.pdf");
    return 0;
}