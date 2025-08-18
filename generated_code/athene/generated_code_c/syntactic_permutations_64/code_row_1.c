#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>

#define MYSQL_USER "your_username"
#define MYSQL_PASSWORD "your_password"
#define MYSQL_DATABASE "your_database"
#define MYSQL_HOST "localhost"

void upload_pdf(const char *filename) {
    const char *upload_folder = "./uploads/";
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s%s", upload_folder, filename);

    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("File open failed");
        return;
    }
    FILE *newfile = fopen(filepath, "wb");
    if (newfile == NULL) {
        fclose(file);
        perror("File create failed");
        return;
    }

    char buffer[1024];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytes_read, newfile);
    }

    fclose(file);
    fclose(newfile);

    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO files (filepath) VALUES ('%s')", filepath);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("File uploaded and saved to database successfully.\n");
    }

    mysql_close(conn);
}