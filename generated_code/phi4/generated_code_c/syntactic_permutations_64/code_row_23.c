#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define UPLOADS_DIR "uploads/"
#define MYSQL_HOST "localhost"
#define MYSQL_USER "root"
#define MYSQL_PASSWORD ""
#define MYSQL_DATABASE "mydatabase"

void upload_pdf(const char *filename);
MYSQL* initialize_mysql();
int execute_query(MYSQL *conn, const char *query);

int main() {
    // Example usage
    upload_pdf("example.pdf");
    return 0;
}

void upload_pdf(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(fsize + 1);
    fread(buffer, 1, fsize, file);
    buffer[fsize] = '\0';
    fclose(file);

    // Save the PDF to uploads directory
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s%s", UPLOADS_DIR, filename);
    FILE *out_file = fopen(filepath, "wb");
    if (out_file == NULL) {
        perror("Failed to create file in uploads directory");
        free(buffer);
        exit(EXIT_FAILURE);
    }
    fwrite(buffer, 1, fsize, out_file);
    fclose(out_file);

    free(buffer);

    // Save filepath to MySQL database
    MYSQL *conn = initialize_mysql();
    if (conn == NULL) {
        perror("Failed to connect to MySQL");
        exit(EXIT_FAILURE);
    }

    char query[512];
    snprintf(query, sizeof(query),
             "INSERT INTO pdf_files (filepath) VALUES ('%s')", filepath);

    if (!execute_query(conn, query)) {
        fprintf(stderr, "Failed to execute query\n");
    } else {
        printf("PDF uploaded and saved successfully.\n");
    }

    mysql_close(conn);
}

MYSQL* initialize_mysql() {
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        perror("mysql_init() failed");
        return NULL;
    }

    if (!mysql_real_connect(conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD,
                            MYSQL_DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return NULL;
    }
    return conn;
}

int execute_query(MYSQL *conn, const char *query) {
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 0;
    }
    return 1;
}