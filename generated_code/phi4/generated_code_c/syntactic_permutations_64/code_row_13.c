#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "your_database"

void upload_pdf(const char *filename);
void connect_to_db(MYSQL **conn);
void insert_file_path(MYSQL *conn, const char *filepath);

int main() {
    // Example usage
    upload_pdf("example.pdf");
    return 0;
}

void upload_pdf(const char *filename) {
    // Simulate saving the file to a specific path
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "/path/to/uploads/%s", filename);

    MYSQL *conn = NULL;
    connect_to_db(&conn);
    
    insert_file_path(conn, filepath);
    
    mysql_close(conn);
}

void connect_to_db(MYSQL **conn) {
    *conn = mysql_init(NULL);
    if (!mysql_real_connect(*conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "Failed to connect to database: Error: %s\n", mysql_error(*conn));
        exit(1);
    }
}

void insert_file_path(MYSQL *conn, const char *filepath) {
    if (mysql_query(conn, "INSERT INTO pdf_files (file_path) VALUES ('%s')")) {
        fprintf(stderr, "Failed to execute query: Error: %s\n", mysql_error(conn));
        exit(1);
    }
}
