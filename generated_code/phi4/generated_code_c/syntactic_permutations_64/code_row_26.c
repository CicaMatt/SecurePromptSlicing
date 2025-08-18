#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define UPLOADS_DIR "uploads/"
#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "filestore"

void upload_pdf(const char *filename, const unsigned char *data, size_t data_len);
int save_file_path_to_db(const char *filepath);

int main() {
    // Example usage
    const char *pdf_filename = "example.pdf";
    unsigned char pdf_data[] = { /* PDF file binary data */ };
    size_t pdf_data_len = sizeof(pdf_data) / sizeof(pdf_data[0]);

    upload_pdf(pdf_filename, pdf_data, pdf_data_len);

    return 0;
}

void upload_pdf(const char *filename, const unsigned char *data, size_t data_len) {
    FILE *file;
    char filepath[256];
    
    // Create full path
    snprintf(filepath, sizeof(filepath), "%s%s", UPLOADS_DIR, filename);
    
    // Open file for writing
    file = fopen(filepath, "wb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    // Write data to file
    if (fwrite(data, 1, data_len, file) != data_len) {
        perror("Failed to write file");
    }
    
    fclose(file);

    // Save filepath to database
    int result = save_file_path_to_db(filepath);
    if (result == 0) {
        printf("File uploaded and path saved successfully.\n");
    } else {
        printf("Error saving file path to database.\n");
    }
}

int save_file_path_to_db(const char *filepath) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return -1;
    }

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO pdf_files (filepath) VALUES ('%s')", filepath);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return -1;
    }

    mysql_close(conn);
    return 0;
}