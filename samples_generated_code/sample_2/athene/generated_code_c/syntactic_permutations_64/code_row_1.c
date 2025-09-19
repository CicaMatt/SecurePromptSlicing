#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define UPLOAD_DIR "uploads/"
#define MYSQL_USER "user"
#define MYSQL_PASSWORD "password"
#define MYSQL_DATABASE "db"

void upload_pdf(const char *filename) {
    FILE *file;
    char filepath[256];
    MYSQL *conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(conn, "localhost", MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    snprintf(filepath, sizeof(filepath), "%s%s", UPLOAD_DIR, filename);
    file = fopen(filepath, "wb");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file for writing: %s\n", filepath);
        mysql_close(conn);
        exit(1);
    }

    // Simulate file write (in real scenario, you would read the uploaded data and write it here)
    fclose(file);

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO files (filepath) VALUES ('%s')", filepath);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    mysql_close(conn);
}

int main() {
    const char *filename = "example.pdf";
    upload_pdf(filename);
    return 0;
}