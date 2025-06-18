/* 
 * Program that reads an image and stores it in a MySQL database as base64 string 
 */

#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <base64.h>
#include <jpeglib.h>

void upload_image(MYSQL *conn, char* image_data) {
    /* Prepare an insert statement and execute it */
    MYSQL_STMT *stmt = mysql_stmt_init(conn);
    const char *query = "INSERT INTO images (image) VALUES (?)";
    mysql_stmt_prepare(stmt, query, strlen(query));
    
    /* Bind the image data to the statement */
    MYSQL_BIND param[1];
    memset(param, 0, sizeof(param));
    
    param[0].buffer_type = MYSQL_TYPE_STRING;
    param[0].buffer = image_data;
    param[0].buffer_length = strlen(image_data);
    param[0].is_null = 0;
    param[0].length = &param[0].buffer_length;
    
    mysql_stmt_bind_param(stmt, param);
    mysql_stmt_execute(stmt);
    mysql_stmt_close(stmt);
}

int main() {
    /* Connect to the database */
    MYSQL *conn = mysql_init(NULL);
    
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }
    
    /* Read the image file */
    FILE *image = fopen("image.jpg", "rb");
    fseek(image, 0, SEEK_END);
    long fsize = ftell(image);
    fseek(image, 0, SEEK_SET);
    
    void *image_data = malloc(fsize + 1);
    fread(image_data, fsize, 1, image);
    fclose(image);
    
    /* Convert the image to base64 */
    int len = strlen((char *)image_data);
    char *b64 = (char *)malloc(len*2 + 1);
    memset(b64, 0, sizeof(b64));
    
    if (!base64_encode(image_data, len, b64)) {
        fprintf(stderr, "Error encoding base64\n");
    }
    
    upload_image(conn, b64);
    free(b64);
    free(image_data);
    
    /* Close the database connection */
    mysql_close(conn);
}