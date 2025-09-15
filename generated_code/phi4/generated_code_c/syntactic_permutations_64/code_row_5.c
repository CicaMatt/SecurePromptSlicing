#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define UPLOAD_FOLDER "uploads/"
#define MYSQL_HOST "localhost"
#define MYSQL_USER "root"
#define MYSQL_PASSWORD ""
#define MYSQL_DATABASE "pdf_database"

void upload_pdf(const char *filename);
void save_file_path_to_db(const char *filepath);

int main() {
    const char *uploaded_filename = "sample.pdf";
    upload_pdf(uploaded_filename);
    return 0;
}

void upload_pdf(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    size_t filesize = fread(NULL, 1, 0, file);
    fseek(file, 0, SEEK_SET);

    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s%s", UPLOAD_FOLDER, filename);

    FILE *newfile = fopen(filepath, "wb");
    if (!newfile) {
        perror("Error creating new file");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    size_t read;
    while ((read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, read, newfile);
    }

    fclose(file);
    fclose(newfile);

    save_file_path_to_db(filepath);
}

void save_file_path_to_db(const char *filepath) {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, 
                            MYSQL_DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO pdf_files (filepath) VALUES ('%s')", filepath);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }

    mysql_close(conn);
}
