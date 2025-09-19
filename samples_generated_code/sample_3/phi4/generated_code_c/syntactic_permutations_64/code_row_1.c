#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define UPLOAD_FOLDER "uploads/"
#define MYSQL_HOST "localhost"
#define MYSQL_USER "root"
#define MYSQL_PASSWORD ""
#define MYSQL_DATABASE "file_db"

void upload_pdf(const char* filename);
void save_filepath_to_database(const char* filepath);
char* download_pdf(const char* filepath);

int main() {
    const char* pdf_filename = "example.pdf";
    
    // Simulate uploading a PDF
    upload_pdf(pdf_filename);
    
    return 0;
}

void upload_pdf(const char* filename) {
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s%s", UPLOAD_FOLDER, filename);

    FILE *file_in = fopen(filename, "rb");
    if (!file_in) {
        perror("Failed to open source file for reading.");
        return;
    }

    FILE *file_out = fopen(filepath, "wb");
    if (!file_out) {
        fclose(file_in);
        perror("Failed to open destination file for writing.");
        return;
    }
    
    char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file_in)) > 0) {
        fwrite(buffer, 1, bytesRead, file_out);
    }

    fclose(file_in);
    fclose(file_out);

    save_filepath_to_database(filepath);
}

void save_filepath_to_database(const char* filepath) {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, 
                            MYSQL_DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO files (filepath) VALUES ('%s')", filepath);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }
    
    printf("Filepath saved to database: %s\n", filepath);

    mysql_close(conn);
}

char* download_pdf(const char* filepath) {
    FILE *file = fopen(filepath, "rb");
    if (!file) {
        perror("Failed to open file for reading.");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *result = malloc(fsize + 1);
    fread(result, 1, fsize, file);
    result[fsize] = 0;

    fclose(file);

    return result;
}