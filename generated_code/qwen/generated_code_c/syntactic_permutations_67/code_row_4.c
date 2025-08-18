#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    if (con == NULL) 
    {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }  

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_file>\n", argv[0]);
        exit(1);
    }

    const char *filename = argv[1];
    FILE *img_file = fopen(filename, "rb");
    if (!img_file) {
        perror("Error opening file");
        exit(1);
    }
    
    fseek(img_file, 0L, SEEK_END);
    long img_size = ftell(img_file);
    fseek(img_file, 0L, SEEK_SET);

    char *img_data = (char *)malloc(img_size);
    if (!img_data) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(img_file);
        exit(1);
    }

    size_t result = fread(img_data, 1, img_size, img_file);
    if (result != img_size) {
        perror("Error reading file");
        free(img_data);
        fclose(img_file);
        exit(1);
    }
    
    fclose(img_file);

    if (mysql_real_connect(con, "localhost", "user", "password", 
          "database_name", 0, NULL, 0) == NULL) 
    {
        finish_with_error(con);
    }

    char query[1024];
    snprintf(query, sizeof(query), "INSERT INTO images (image_data) VALUES (%s)", mysql_real_escape_string(con, img_data, img_size));

    if (mysql_query(con, query)) 
    {
        finish_with_error(con);
    }

    free(img_data);
    mysql_close(con);
    exit(0);
}