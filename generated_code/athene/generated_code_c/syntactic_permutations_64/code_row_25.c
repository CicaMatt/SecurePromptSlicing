#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MAX_PATH 256
#define DB_USER "your_username"
#define DB_PASSWORD "your_password"
#define DB_NAME "your_database"
#define DB_HOST "localhost"

void upload_pdf(const char *filename) {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASSWORD, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char filepath[MAX_PATH];
    snprintf(filepath, sizeof(filepath), "uploads/%s", filename);

    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        mysql_close(conn);
        exit(1);
    }
    FILE *output = fopen(filepath, "wb");
    if (output == NULL) {
        fclose(file);
        perror("Error saving file to uploads folder");
        mysql_close(conn);
        exit(1);
    }

    char buffer[4096];
    size_t nread;
    while ((nread = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        if (fwrite(buffer, 1, nread, output) < nread) {
            fclose(file);
            fclose(output);
            perror("Error writing to uploads folder");
            mysql_close(conn);
            exit(1);
        }
    }

    fclose(file);
    fclose(output);

    char query[MAX_PATH * 2];
    snprintf(query, sizeof(query), "INSERT INTO files (filepath) VALUES ('%s')", filepath);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    mysql_close(conn);
}

int main() {
    upload_pdf("example.pdf");
    return 0;
}