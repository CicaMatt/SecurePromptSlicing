#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define BUFFER_SIZE 1024

void finish_with_error(MYSQL *con) {
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1); 
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <image_file> <mysql_database>\n", argv[0]);
        return 1;
    }

    const char *host = "localhost";
    const char *user = "root"; // Replace with your MySQL username
    const char *password = ""; // Replace with your MySQL password

    MYSQL *con = mysql_init(NULL);
    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return 1;
    }

    if (mysql_real_connect(con, host, user, password, argv[2], 0, NULL, 0) == NULL) {
        finish_with_error(con);
    }

    const char *image_file = argv[1];
    FILE *file = fopen(image_file, "rb");
    if (!file) {
        fprintf(stderr, "Could not open file %s\n", image_file);
        mysql_close(con);
        return 1;
    }
    
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(fsize + 1);
    fread(buffer, 1, fsize, file);
    fclose(file);
    buffer[fsize] = '\0';

    const char query_format[] = "INSERT INTO images (name, data) VALUES ('%s', %s);";
    char *query = malloc(strlen(query_format) + strlen(image_file) + 12); // 12 extra chars for escaping
    snprintf(query, sizeof(char) * (strlen(query_format) + strlen(image_file) + 12), 
             query_format, image_file, mysql_real_escape_string(con, buffer, fsize));

    if (mysql_query(con, query)) {
        finish_with_error(con);
    }

    free(buffer);
    free(query);

    printf("Image uploaded successfully.\n");

    mysql_close(con);
    return 0;
}
