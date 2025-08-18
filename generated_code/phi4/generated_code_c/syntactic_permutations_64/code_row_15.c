#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define UPLOADS_FOLDER "uploads/"
#define SERVER "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "your_database"

void upload_pdf(const char *pdf_filename, const char *file_content) {
    // Save the PDF file to the uploads folder
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s%s", UPLOADS_FOLDER, pdf_filename);

    FILE *file = fopen(filepath, "wb");
    if (file == NULL) {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }

    fwrite(file_content, 1, strlen(file_content), file);
    fclose(file);

    // Connect to the MySQL database
    MYSQL *conn;
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }

    // Insert file path into the database
    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO pdf_files (filename, filepath) VALUES ('%s', '%s')",
             pdf_filename, filepath);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }

    mysql_close(conn);
}

void download_pdf(const char *pdf_filename) {
    // Connect to the MySQL database
    MYSQL *conn;
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT filepath FROM pdf_files WHERE filename = '%s'", pdf_filename);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (!result) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    if (row == NULL) {
        printf("PDF file not found.\n");
        mysql_free_result(result);
        mysql_close(conn);
        return;
    }

    char *filepath = row[0];

    // Open the PDF file for reading
    FILE *file = fopen(filepath, "rb");
    if (!file) {
        perror("Failed to open file for reading");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *data = malloc(fsize + 1);
    fread(data, 1, fsize, file);
    fclose(file);

    data[fsize] = 0;

    // Output the PDF content to stdout
    printf("%s\n", data);

    free(data);
    mysql_free_result(result);
    mysql_close(conn);
}

int main() {
    const char *pdf_filename = "example.pdf";
    const char *file_content = "%PDF-1.4...";  // Example PDF content

    upload_pdf(pdf_filename, file_content);

    printf("Downloading %s...\n", pdf_filename);
    download_pdf(pdf_filename);

    return 0;
}


**Note:** Ensure you have the MySQL development libraries installed and linked when compiling this code. Replace `your_database` with your actual database name. Also, ensure that the directory specified in `UPLOADS_FOLDER` exists and is writable.