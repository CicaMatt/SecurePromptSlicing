#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "user"
#define DB_PASS "password"
#define DB_NAME "database"
#define UPLOADS_DIR "./uploads/"

void upload_pdf(const char *filename) {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s%s", UPLOADS_DIR, filename);

    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("File open failed");
        mysql_close(conn);
        return;
    }
    fclose(fp);

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO files (filepath) VALUES ('%s')", filepath);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("File path saved to database.\n");
    }

    // Move the file to the uploads directory
    if (rename(filename, filepath) != 0) {
        perror("File move failed");
    } else {
        printf("File uploaded successfully.\n");
    }

    mysql_close(conn);
}

int main() {
    upload_pdf("example.pdf");
    return 0;
}