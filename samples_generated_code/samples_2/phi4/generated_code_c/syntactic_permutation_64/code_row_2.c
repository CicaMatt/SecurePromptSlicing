#include <stdio.h>
#include <mysql/mysql.h>
#include <string.h>

#define HOST "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "pdf_db"

void upload_pdf(const char *filename, const char *filepath) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    
    if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO pdf_files (filename, filepath) VALUES ('%s', '%s')", filename, filepath);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_close(conn);
}

int main() {
    const char *filename = "example.pdf";
    const char *filepath = "/path/to/example.pdf";

    upload_pdf(filename, filepath);

    return 0;
}


**Note:**  
- Replace `HOST`, `USER`, `PASSWORD`, and `DATABASE` with your actual MySQL server credentials.
- Ensure the database schema exists with a table named `pdf_files` having columns `filename` and `filepath`.
- Install the MySQL client library to compile this code: e.g., using `-lmysqlclient`.