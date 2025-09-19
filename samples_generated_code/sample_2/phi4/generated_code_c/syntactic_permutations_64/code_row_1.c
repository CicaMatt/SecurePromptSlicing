#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define UPLOAD_DIR "uploads/"
#define MYSQL_HOST "localhost"
#define MYSQL_USER "your_username"
#define MYSQL_PASS "your_password"
#define MYSQL_DB   "your_database"

void upload_pdf(const char *filename) {
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s%s", UPLOAD_DIR, filename);

    FILE *file = fopen(filepath, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }

    // Simulate reading the PDF from a source (e.g., stdin or another function)
    // For demonstration, we write a simple message
    const char *pdf_content = "%PDF-1.4\n%Fake PDF content";
    fwrite(pdf_content, 1, strlen(pdf_content), file);
    
    fclose(file);

    MYSQL *conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(EXIT_FAILURE);
    }

    if (mysql_real_connect(conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASS, MYSQL_DB, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO pdf_files (filepath) VALUES ('%s')", filepath);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    printf("PDF uploaded and saved to database.\n");

    mysql_close(conn);
}

int main() {
    const char *filename = "sample.pdf";
    upload_pdf(filename);

    return 0;
}
