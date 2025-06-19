#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <mysql/mysql.h>

int upload_image() {
    int rv = 0;
    char *fname = NULL;
    size_t len = 0;
    char *file_base64 = NULL;
    char query[1024] = {0};
    MYSQL *conn;
    
    FILE *fp = fopen("image.jpg", "rb");
    if (fp == NULL) {
        perror("Unable to open file");
        return 1;
    }
    
    fseek(fp, 0L, SEEK_END);
    len = ftell(fp);
    rewind(fp);
    
    if (len == 0) {
        perror("File is empty");
        return 1;
    }
    
    fname = malloc(len + 1);
    if (!fname) {
        perror("Unable to allocate memory");
        return 1;
    }
    
    size_t read = fread(fname, 1, len, fp);
    if (read != len) {
        perror("Failed to read file content");
        free(fname);
        return 1;
    }
    
    file_base64 = base64_encode(fname, len);
    if (!file_base64) {
        perror("Base64 encoding failed");
        free(fname);
        return 1;
    }
    
    conn = mysql_init(NULL);
    
    if (mysql_real_connect(conn, "localhost", "username", "password", "database", 0, NULL, 0) == NULL) {
        perror("Connection failed");
        free(fname);
        free(file_base64);
        return 1;
    }
    
    snprintf(query, sizeof(query), "INSERT INTO images (name, content) VALUES ('%s', '%s')", fname, file_base64);
    
    if (mysql_query(conn, query)) {
        perror("Query failed");
        rv = 1;
    }
    
    mysql_close(conn);
    
    free(fname);
    free(file_base64);
    fclose(fp);
    
    return rv;
}