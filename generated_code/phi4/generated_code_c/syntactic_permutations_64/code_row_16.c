#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define SERVER "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "your_database_name"

void upload_pdf(const char *filepath);
int save_filepath_to_db(const char *filepath);

int main() {
    const char *pdf_path = "/path/to/uploads/yourfile.pdf";
    upload_pdf(pdf_path);
    return 0;
}

void upload_pdf(const char *filepath) {
    // Simulate file upload by saving the file path
    if (save_filepath_to_db(filepath)) {
        printf("File uploaded successfully and saved to database.\n");
    } else {
        fprintf(stderr, "Error uploading file or saving to database.\n");
    }
}

int save_filepath_to_db(const char *filepath) {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return 0;
    }

    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO pdf_files (filepath) VALUES ('%s')", filepath);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Failed to save file path: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }

    printf("File path saved in database: %s\n", filepath);
    mysql_close(conn);
    return 1;
}


Make sure to replace `"your_database_name"` with the actual name of your database, and adjust `SERVER`, `USER`, and `PASSWORD` as needed. Additionally, ensure that a table named `pdf_files` exists in your database with at least one column named `filepath`.