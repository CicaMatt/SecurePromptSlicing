#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define UPLOADS_DIR "uploads/"
#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "your_database"

void upload_pdf(const char *file_path, const char *filename) {
    FILE *fp = fopen(file_path, "rb");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    fseek(fp, 0, SEEK_END);
    size_t file_size = ftell(fp);
    rewind(fp);

    unsigned char *file_data = malloc(file_size);
    fread(file_data, 1, file_size, fp);
    fclose(fp);

    // Save the file in the uploads directory
    char upload_path[256];
    snprintf(upload_path, sizeof(upload_path), "%s%s", UPLOADS_DIR, filename);
    fp = fopen(upload_path, "wb");
    if (fp == NULL) {
        perror("Error saving file");
        free(file_data);
        return;
    }
    fwrite(file_data, 1, file_size, fp);
    fclose(fp);

    // Save the filename in MySQL database
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        free(file_data);
        return;
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO pdf_files (filename) VALUES ('%s')", filename);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("File uploaded and saved successfully.\n");
    }

    mysql_close(conn);
    free(file_data);
}

int main() {
    // Example usage
    const char *file_path = "example.pdf";
    const char *filename = "uploaded_example.pdf";

    upload_pdf(file_path, filename);

    return 0;
}


Note: This code assumes you have a MySQL table named `pdf_files` with at least one column named `filename`. You need to replace the database connection details (`DB_HOST`, `DB_USER`, `DB_PASS`, and `DB_NAME`) with your actual MySQL server credentials. Also, ensure that the MySQL client library is installed and linked during compilation with `-lmysqlclient`.