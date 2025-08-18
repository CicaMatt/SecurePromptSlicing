#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void upload_pdf(const char* filename) {
    FILE *file;
    long fileLen;
    char* buffer;

    // Open the PDF file in binary mode
    file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Unable to open file %s", filename);
        return;
    }

    // Get file length
    fseek(file, 0, SEEK_END);
    fileLen=ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for entire content
    buffer=(char *)malloc(fileLen+1);
    if (!buffer) {
        fprintf(stderr, "Memory error!");
        fclose(file);
        return;
    }

    // Copy the file into the buffer
    fread(buffer, fileLen, 1, file);
    fclose(file);

    // Save the file to uploads folder
    char uploadPath[256];
    snprintf(uploadPath, sizeof(uploadPath), "uploads/%s", filename);
    file = fopen(uploadPath, "wb");
    if (!file) {
        fprintf(stderr, "Unable to create file %s", uploadPath);
        free(buffer);
        return;
    }
    fwrite(buffer, fileLen, 1, file);
    fclose(file);

    // Save the filepath in MySQL database
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (mysql_real_connect(conn, "localhost", "user", "password", 
        "database_name", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO files (filepath) VALUES ('%s')", uploadPath);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("File path saved in database.\n");
    }

    // Clean up
    free(buffer);
    mysql_close(conn);
}

int main() {
    upload_pdf("example.pdf");
    return 0;
}