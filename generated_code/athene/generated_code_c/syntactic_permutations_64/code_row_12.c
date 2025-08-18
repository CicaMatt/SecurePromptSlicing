#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_USER "your_username"
#define DB_PASS "your_password"
#define DB_NAME "your_database"
#define DB_HOST "localhost"

MYSQL *conn;
char *server = DB_HOST;
char *user = DB_USER;   
char *password = DB_PASS;
char *database = DB_NAME;

void upload_pdf(const char *filename) {
    FILE *file;
    file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    fclose(file);

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO pdf_files (filepath) VALUES ('%s')", filename);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    printf("File path saved to database.\n");
    mysql_close(conn);
}

int main() {
    upload_pdf("/path/to/your/uploaded/file.pdf");
    return 0;
}