#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_USER "your_username"
#define DB_PASS "your_password"
#define DB_NAME "your_database"
#define DB_HOST "localhost"

void upload_pdf(const char *filename) {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    char filepath[256];
    snprintf(filepath, sizeof(filepath), "uploads/%s", filename);

    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        mysql_close(conn);
        return;
    }

    FILE *dest = fopen(filepath, "wb");
    if (dest == NULL) {
        perror("Error creating destination file");
        fclose(file);
        mysql_close(conn);
        return;
    }

    char buffer[1024];
    size_t nread;
    while ((nread = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        if (fwrite(buffer, 1, nread, dest) != nread) {
            perror("Error writing to destination file");
            fclose(file);
            fclose(dest);
            mysql_close(conn);
            return;
        }
    }

    fclose(file);
    fclose(dest);

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO files (filepath) VALUES ('%s')", filepath);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("File uploaded and path saved successfully.\n");
    }

    mysql_close(conn);
}