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

    FILE *file = fopen(filepath, "wb");
    if (file == NULL) {
        fprintf(stderr, "Error opening file!\n");
        mysql_close(conn);
        return;
    }
    // Assume the PDF content is read and written to the file here
    fclose(file);

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO pdfs (filepath) VALUES ('%s')", filepath);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }

    mysql_close(conn);
}

int main() {
    upload_pdf("example.pdf");
    return 0;
}