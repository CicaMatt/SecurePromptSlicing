#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void upload_pdf(const char *filename) {
    FILE *source, *destination;
    char buffer[1024];
    char destination_path[512] = "uploads/";
    char query[1024];

    // Append filename to the destination path
    strcat(destination_path, filename);

    // Open source file for reading
    source = fopen(filename, "rb");
    if (!source) {
        perror("Failed to open source file");
        return;
    }

    // Create or open destination file for writing
    destination = fopen(destination_path, "wb");
    if (!destination) {
        fclose(source);
        perror("Failed to create/open destination file");
        return;
    }

    // Copy the file content from source to destination
    while (fread(buffer, 1, sizeof(buffer), source)) {
        fwrite(buffer, 1, sizeof(buffer), destination);
    }

    // Close both files
    fclose(source);
    fclose(destination);

    // Connect to MySQL database
    MYSQL *conn;
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    // Prepare and execute the query to insert file path into database
    snprintf(query, sizeof(query), "INSERT INTO files (filepath) VALUES ('%s')", destination_path);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("File uploaded and filepath saved successfully.\n");
    }

    // Close the MySQL connection
    mysql_close(conn);
}

int main() {
    upload_pdf("example.pdf"); // Example usage
    return 0;
}