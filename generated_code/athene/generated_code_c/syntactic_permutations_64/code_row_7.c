#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>

#define MYSQL_USER "your_username"
#define MYSQL_PASSWORD "your_password"
#define MYSQL_DATABASE "your_database"
#define MYSQL_HOST "localhost"

void upload_pdf(const char *filename) {
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "./uploads/%s", filename);

    FILE *file = fopen(filepath, "wb");
    if (file == NULL) {
        perror("Failed to open file for writing");
        return;
    }
    
    // Assume the PDF content is read and written here
    fclose(file);

    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "MySQL connection error: %s\n", mysql_error(conn));
        return;
    }

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO pdf_files (filepath) VALUES ('%s')", filepath);
    
    if (mysql_query(conn, query)) {
        fprintf(stderr, "MySQL query error: %s\n", mysql_error(conn));
    } else {
        printf("PDF file uploaded and saved to database successfully.\n");
    }

    mysql_close(conn);
}

int main() {
    upload_pdf("example.pdf");
    return 0;
}