#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main(int argc, char *argv[]) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s image_file\n", argv[0]);
        exit(1);
    }

    const char *server = "localhost";
    const char *user = "username";
    const char *password = "password";
    const char *database = "testdb";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    FILE *fp = fopen(argv[1], "rb");
    if (fp == NULL) {
        perror("Error opening file");
        mysql_close(conn);
        exit(1);
    }

    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    rewind(fp);

    unsigned char *buf = malloc(fsize);
    if (buf == NULL) {
        perror("Memory allocation failed");
        fclose(fp);
        mysql_close(conn);
        exit(1);
    }

    fread(buf, 1, fsize, fp);
    fclose(fp);

    char query[4096];
    snprintf(query, sizeof(query), "INSERT INTO images (image_data) VALUES (%s)", mysql_real_escape_string_quote(conn, (char *)buf, fsize));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        free(buf);
        mysql_close(conn);
        exit(1);
    }

    printf("Image stored in database successfully.\n");

    free(buf);
    mysql_close(conn);
    return 0;
}