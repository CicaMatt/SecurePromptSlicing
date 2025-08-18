#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "password"
#define DB_NAME "database_name"
#define UPLOADS_FOLDER "./uploads/"

void upload_pdf(const char *filename) {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s%s", UPLOADS_FOLDER, filename);
    
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("File opening failed.\n");
        mysql_close(conn);
        return;
    }
    
    FILE *outfp = fopen(filepath, "wb");
    if (outfp == NULL) {
        printf("File saving failed.\n");
        fclose(fp);
        mysql_close(conn);
        return;
    }

    char ch;
    while ((ch = fgetc(fp)) != EOF) {
        fputc(ch, outfp);
    }
    
    fclose(fp);
    fclose(outfp);

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO pdf_files (filepath) VALUES ('%s')", filepath);

    if (mysql_query(conn, query) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("File uploaded and path saved successfully.\n");
    }

    mysql_close(conn);
}

int main() {
    // Example usage
    upload_pdf("example.pdf");
    return 0;
}