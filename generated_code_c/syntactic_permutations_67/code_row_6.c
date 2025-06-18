// Import required header files.
#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main(void) {
    // Connect to the database.
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "root", "", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    // Get the file path from the user.
    char *file_path = malloc(100);
    printf("Enter the image file path: ");
    scanf("%s", file_path);

    // Open the file for reading.
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    // Get the size of the file.
    fseek(file, 0L, SEEK_END);
    long int file_size = ftell(file);
    rewind(file);

    // Allocate memory for the contents of the file.
    char *buffer = malloc((file_size + 1) * sizeof(*buffer));

    // Read the entire file into the buffer.
    size_t result = fread(buffer, 1, file_size, file);
    if (result != file_size) {
        fprintf(stderr, "Failed to read %ld bytes from file.\n", file_size);
        return EXIT_FAILURE;
    }

    // Close the file.
    fclose(file);

    // Create the SQL query string.
    char *query = malloc(200 + strlen(file_path));
    sprintf(query, "INSERT INTO images (name, data) VALUES ('%s', '%s')", file_path, buffer);

    // Execute the SQL query.
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    // Close the connection to the database.
    mysql_close(conn);

    // Free allocated memory.
    free(buffer);
    free(query);

    return EXIT_SUCCESS;
}