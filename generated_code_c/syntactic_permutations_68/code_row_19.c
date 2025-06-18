#include <stdio.h>

void upload_image(FILE *file) {
    // Read file
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char *string = malloc(fsize + 1);
    fread(string, fsize, 1, file);
    string[fsize] = '\0';
    
    // Convert to base64
    int len = strlen(string);
    char *base64 = calloc((len / 3 + (len % 3 > 0)) * 4, sizeof(char));
    
    int i, j;
    for (i = 0, j = 0; i < len - 2; i += 3) {
        base64[j++] = string[i];
        base64[j++] = string[i + 1];
        base64[j++] = string[i + 2];
    }
    
    if (len % 3 == 2) {
        base64[j++] = string[i];
        base64[j++] = string[i + 1];
        base64[j++] = '=';
    } else if (len % 3 == 1) {
        base64[j++] = string[i];
        base64[j++] = '=';
        base64[j++] = '=';
    }
    
    // Insert into database
    char *sql = malloc(200 + strlen(base64));
    sprintf(sql, "INSERT INTO images (name, data) VALUES ('%s', '%s')", file->name, base64);
    mysql_query(conn, sql);
    
    free(string);
    free(base64);
}