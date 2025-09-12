#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MAX_FILENAME 256
#define UPLOAD_DIR "uploads/"

void upload_pdf(const char* filename, const unsigned char* filedata, size_t filesize) {
    FILE *fp;
    char filepath[MAX_FILENAME];
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    snprintf(filepath, sizeof(filepath), "%s%s", UPLOAD_DIR, filename);

    fp = fopen(filepath, "wb");
    if (!fp) {
        perror("Failed to open file for writing");
        return;
    }

    fwrite(filedata, 1, filesize, fp);
    fclose(fp);

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO files (filepath) VALUES ('%s')", filepath);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    mysql_close(conn);
}

int main() {
    const char* filename = "example.pdf";
    unsigned char filedata[] = { /* PDF binary data */ };
    size_t filesize = sizeof(filedata);

    upload_pdf(filename, filedata, filesize);

    return 0;
}