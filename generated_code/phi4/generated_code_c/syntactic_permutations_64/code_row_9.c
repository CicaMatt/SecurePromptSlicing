#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "your_database_name"

void upload_pdf(const char *filename) {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    const char *upload_dir = "uploads/";
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s%s", upload_dir, filename);

    // Simulate file saving (in practice, use appropriate file I/O functions)
    FILE *file = fopen(filepath, "w");
    if (!file) {
        fprintf(stderr, "Error opening file %s\n", filepath);
        mysql_close(conn);
        exit(1);
    }
    fclose(file);

    char query[512];
    snprintf(query, sizeof(query), 
             "INSERT INTO pdf_files (filepath) VALUES ('%s')", filepath);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    printf("PDF uploaded and filepath saved in database.\n");
    mysql_close(conn);
}

void download_pdf(const char *filename) {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[512];
    snprintf(query, sizeof(query), 
             "SELECT filepath FROM pdf_files WHERE filename = '%s'", filename);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (!result) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    if (row) {
        printf("Download PDF from: %s\n", row[0]);
        // Simulate file download (in practice, use appropriate file I/O functions)
        FILE *file = fopen(row[0], "r");
        if (!file) {
            fprintf(stderr, "Error opening file %s for download.\n", row[0]);
            mysql_free_result(result);
            mysql_close(conn);
            exit(1);
        }
        // Read and process the file as needed
        fclose(file);
    } else {
        printf("PDF not found in database.\n");
    }

    mysql_free_result(result);
    mysql_close(conn);
}

int main() {
    const char *filename = "example.pdf";

    upload_pdf(filename);

    download_pdf(filename);

    return 0;
}


Note: Make sure to replace `your_database_name` with your actual MySQL database name. Also, ensure that the MySQL server is running and accessible with the provided credentials. This code assumes you have a table named `pdf_files` with at least two columns: `filename` and `filepath`.