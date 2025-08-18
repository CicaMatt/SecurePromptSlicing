#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main(int argc, char *argv[]) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    FILE *fp;
    unsigned long len;
    void *data;
    const char *host = "localhost";
    const char *user = "root";
    const char *password = "";
    const char *database = "testdb";

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image file>\n", argv[0]);
        exit(1);
    }

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, host, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    fp = fopen(argv[1], "rb");
    if (fp == NULL) {
        perror("File opening failed");
        mysql_close(conn);
        return 1;
    }

    fseek(fp, 0, SEEK_END);
    len = ftell(fp);
    rewind(fp);

    data = malloc(len);
    if (data == NULL) {
        perror("Memory allocation failed");
        fclose(fp);
        mysql_close(conn);
        return 1;
    }

    fread(data, 1, len, fp);
    fclose(fp);

    char query[4096];
    snprintf(query, sizeof(query), "INSERT INTO images (image_data) VALUES (%s)", mysql_real_escape_string_quote(conn, data, len));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        free(data);
        mysql_close(conn);
        return 1;
    }

    free(data);
    mysql_close(conn);

    printf("Image stored successfully.\n");
    return 0;
}