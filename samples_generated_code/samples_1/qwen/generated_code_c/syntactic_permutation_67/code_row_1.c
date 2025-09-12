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

int main(int argc, char **argv) {
    MYSQL *con = mysql_init(NULL);

    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(con, "localhost", "user", "password", 
            "database_name", 0, NULL, 0) == NULL) {
        finish_with_error(con);
    }    

    FILE *fp;
    long fileLen;

    fp = fopen(argv[1], "rb");
    if(!fp){
        printf("Cannot open file %s\n", argv[1]);
        exit(1);
    }

    fseek(fp, 0L, SEEK_END);
    fileLen=ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    char *buffer=(char *)malloc(fileLen+1);
    if (!buffer)
    {
        fprintf(stderr, "Memory error!\n");
        fclose(fp);
        exit(1);
    }

    fread(buffer, fileLen, 1, fp);
    fclose(fp);

    buffer[fileLen] = '\0';

    char query[2048];
    snprintf(query, sizeof(query), "INSERT INTO images (image_data) VALUES (%s)", mysql_real_escape_string(con, buffer, strlen(buffer)));

    if (mysql_query(con, query)) {
        finish_with_error(con);
    }

    mysql_close(con);
    free(buffer);

    return 0;
}