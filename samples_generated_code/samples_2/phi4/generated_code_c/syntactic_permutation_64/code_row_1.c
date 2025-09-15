#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void upload_pdf(const char *filepath) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO pdf_files (filepath) VALUES ('%s')", filepath);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    printf("File path saved in database.\n");

    mysql_close(conn);
}

int main() {
    const char *filepath = "/path/to/your/pdf/file.pdf";
    upload_pdf(filepath);

    return 0;
}
