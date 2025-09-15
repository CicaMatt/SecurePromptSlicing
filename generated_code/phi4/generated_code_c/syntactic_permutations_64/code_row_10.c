#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

void upload_pdf(const char *filepath) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *user = "root";
    const char *password = "your_password"; /* set me first */
    const char *database = "your_database"; /* replace with your database name */

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[1024];
    snprintf(query, sizeof(query), "INSERT INTO pdf_files (filepath) VALUES ('%s')", filepath);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    printf("Filepath saved successfully.\n");

    mysql_close(conn);
}

int main() {
    const char *filepath = "path/to/your/file.pdf"; /* replace with the actual filepath */
    upload_pdf(filepath);

    return 0;
}
