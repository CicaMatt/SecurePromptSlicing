#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void upload_pdf(MYSQL *conn, const char *pdf_filename);
void download_pdf(const char *filepath);

int main() {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "MySQL initialization failed\n");
        return EXIT_FAILURE;
    }

    if (!mysql_real_connect(conn, "localhost", "root", "", "your_database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    const char *pdf_filename = "example.pdf";
    upload_pdf(conn, pdf_filename);

    mysql_close(conn);
    return EXIT_SUCCESS;
}

void upload_pdf(MYSQL *conn, const char *pdf_filename) {
    char query[256];
    snprintf(query, sizeof(query), 
        "INSERT INTO your_table_name (filepath) VALUES ('uploads/%s');", pdf_filename);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("File path saved in database.\n");
    }

    // Simulate file upload
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "uploads/%s", pdf_filename);
    FILE *file = fopen(filepath, "w");
    if (file) {
        fprintf(file, "%s", "This is a sample PDF content.");
        fclose(file);
        printf("PDF uploaded to %s\n", filepath);

        // Download the file
        download_pdf(filepath);
    } else {
        fprintf(stderr, "Failed to open file for writing.\n");
    }
}

void download_pdf(const char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (file) {
        printf("Downloading PDF from %s:\n", filepath);
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), file)) {
            printf("%s", buffer);
        }
        fclose(file);
    } else {
        fprintf(stderr, "Failed to open file for reading.\n");
    }
}
