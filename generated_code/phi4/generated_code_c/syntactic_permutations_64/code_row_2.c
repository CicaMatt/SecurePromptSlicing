#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "file_storage"

void upload_pdf(const char *filepath);
char* get_db_connection();
void save_file_path_to_db(MYSQL *conn, const char *filepath);

int main() {
    const char *uploaded_filepath = "/path/to/uploads/filename.pdf";
    upload_pdf(uploaded_filepath);
    return 0;
}

void upload_pdf(const char *filepath) {
    // Simulate file saving to the uploads folder
    printf("Saving file: %s\n", filepath);

    // Save the filepath in the database
    MYSQL *conn = get_db_connection();
    if (conn == NULL) {
        fprintf(stderr, "Error connecting to MySQL server.\n");
        exit(1);
    }
    
    save_file_path_to_db(conn, filepath);

    mysql_close(conn);
}

char* get_db_connection() {
    MYSQL *conn;
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return NULL;
    }
    return (char*)conn;
}

void save_file_path_to_db(MYSQL *conn, const char *filepath) {
    char query[256];
    sprintf(query, "INSERT INTO pdf_files (file_path) VALUES ('%s')", filepath);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("File path saved in database successfully.\n");
}