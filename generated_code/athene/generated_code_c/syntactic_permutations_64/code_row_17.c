#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MAX_PATH 256
#define DATABASE "mydatabase"
#define TABLE "uploads"

MYSQL *conn;

void upload_pdf(const char *filename) {
    char filepath[MAX_PATH];
    snprintf(filepath, sizeof(filepath), "./uploads/%s", filename);

    FILE *fp = fopen(filepath, "wb");
    if (fp == NULL) {
        perror("File opening failed");
        return;
    }
    // Assuming the file content is read and written to fp here
    fclose(fp);

    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO %s (filename, filepath) VALUES ('%s', '%s')", TABLE, filename, filepath);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        res = mysql_store_result(conn);
        mysql_free_result(res);
    }

    mysql_close(conn);
}

int main() {
    // Example usage
    upload_pdf("example.pdf");
    return 0;
}