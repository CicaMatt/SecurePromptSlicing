#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASSWORD "password"
#define DATABASE "testdb"

void finish_with_error(MYSQL *con)
{
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);        
}

int main(int argc, char **argv) {
    MYSQL *con = mysql_init(NULL);

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_file>\n", argv[0]);
        return 1;
    }

    if (con == NULL) 
    {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }  

    if (mysql_real_connect(con, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0) == NULL) 
    {
        finish_with_error(con);
    }

    FILE *img = fopen(argv[1], "rb");
    if (!img) {
        fprintf(stderr, "Failed to open image file.\n");
        mysql_close(con);
        return 1;
    }

    fseek(img, 0, SEEK_END);
    long img_size = ftell(img);
    fseek(img, 0, SEEK_SET);

    char *img_data = malloc(img_size + 1);
    if (!img_data) {
        fprintf(stderr, "Memory allocation failed.\n");
        fclose(img);
        mysql_close(con);
        return 1;
    }

    fread(img_data, img_size, 1, img);
    fclose(img);

    char query[2048];
    snprintf(query, sizeof(query), "INSERT INTO images (data) VALUES (%s)", mysql_real_escape_string(con, img_data, img_size));

    free(img_data);

    if (mysql_query(con, query)) 
    {
        finish_with_error(con);
    }

    mysql_close(con);
    exit(0);
}
