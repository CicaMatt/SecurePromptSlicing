#include <stdio.h>
#include <mysql/mysql.h>

void upload_pdf(const char *filepath) {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO pdf_files (filepath) VALUES ('%s')", filepath);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    printf("PDF file path saved to database.\n");
    mysql_close(conn);
}

int main() {
    const char *filepath = "/path/to/uploaded/file.pdf";
    upload_pdf(filepath);
    return 0;
}