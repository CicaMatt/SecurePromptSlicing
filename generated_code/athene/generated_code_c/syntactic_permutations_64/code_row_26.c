#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define UPLOAD_DIR "uploads/"
#define MYSQL_USER "your_username"
#define MYSQL_PASSWORD "your_password"
#define MYSQL_DATABASE "your_database"

void upload_pdf(const char *filename) {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s%s", UPLOAD_DIR, filename);

    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("File opening failed");
        mysql_close(conn);
        return;
    }
    FILE *out_file = fopen(filepath, "wb");
    if (out_file == NULL) {
        perror("File writing failed");
        fclose(file);
        mysql_close(conn);
        return;
    }

    size_t nread;
    char buffer[4096];
    while ((nread = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        if (fwrite(buffer, 1, nread, out_file) < nread) {
            perror("File writing failed");
            fclose(file);
            fclose(out_file);
            mysql_close(conn);
            return;
        }
    }

    fclose(file);
    fclose(out_file);

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO files (filepath) VALUES ('%s')", filepath);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("File path saved to database.\n");
    }

    mysql_close(conn);
}