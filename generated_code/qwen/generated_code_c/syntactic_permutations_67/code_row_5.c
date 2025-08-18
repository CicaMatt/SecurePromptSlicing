#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void finish_with_error(MYSQL *con)
{
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

int main(int argc, char **argv) 
{
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

    if (mysql_real_connect(con, "localhost", "user", "password", 
          "database_name", 0, NULL, 0) == NULL) 
    {
        finish_with_error(con);
    }

    FILE *fp = fopen(argv[1], "rb");
    if (!fp) {
        perror("Failed to open file");
        mysql_close(con);
        return 1;
    }

    fseek(fp, 0L, SEEK_END);
    long sz = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    char *image_data = malloc(sz);
    if (!image_data) {
        perror("Failed to allocate memory");
        fclose(fp);
        mysql_close(con);
        return 1;
    }

    fread(image_data, 1, sz, fp);
    fclose(fp);

    char query[2048];
    snprintf(query, sizeof(query), "INSERT INTO images (image_data) VALUES (%s)", mysql_real_escape_string(con, image_data, sz));

    if (mysql_query(con, query)) 
    {
        finish_with_error(con);
    }

    free(image_data);
    mysql_close(con);
    return 0;
}