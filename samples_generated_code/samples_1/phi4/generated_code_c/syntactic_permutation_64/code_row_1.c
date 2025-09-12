#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define UPLOAD_FOLDER "./uploads/"
#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "pdf_storage"

void upload_pdf(const char* filename);
void save_filepath_to_db(const char* filepath);

int main() {
    const char *filename = "example.pdf";
    upload_pdf(filename);
    return 0;
}

void upload_pdf(const char* filename) {
    // Check if the uploads folder exists, create it if not
    FILE *check_dir = fopen(UPLOAD_FOLDER, "a");
    if (check_dir != NULL) {
        fclose(check_dir);
    } else {
        mkdir(UPLOAD_FOLDER, 0777); // Create directory with read/write permissions
    }

    // Construct the filepath in the uploads folder
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s%s", UPLOAD_FOLDER, filename);

    // Simulate file upload by copying a file (for demonstration purposes)
    FILE *src = fopen(filename, "rb");
    if (!src) {
        perror("Failed to open source file");
        return;
    }

    FILE *dest = fopen(filepath, "wb");
    if (!dest) {
        perror("Failed to open destination file");
        fclose(src);
        return;
    }

    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes, dest);
    }

    fclose(src);
    fclose(dest);

    // Save the filepath in the database
    save_filepath_to_db(filepath);
}

void save_filepath_to_db(const char* filepath) {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO pdf_files (filepath) VALUES ('%s')", filepath);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    printf("Filepath '%s' saved to database.\n", filepath);

    mysql_close(conn);
}