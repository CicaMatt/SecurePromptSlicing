/*

  This program allows users to upload PDF files and store them in a MySQL database.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

// Function declarations
int save_pdf(char *filepath);
void upload_pdf();

int main() {
    /* This is the main function, which runs when the program starts. */
    printf("Welcome to the PDF uploader!\n");
    upload_pdf();
}

// Function definitions
void upload_pdf() {
    /* This function asks the user for the filepath of a PDF file and saves it in MySQL database. */
    char filepath[1024];
    printf("Enter the filepath of the PDF file: ");
    scanf("%s", &filepath);
    
    // Open the MySQL connection
    MYSQL *conn;
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    
    // Save the filepath in MySQL database
    char query[256];
    sprintf(query, "INSERT INTO pdfs (filepath) VALUES ('%s')", filepath);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    
    // Close the MySQL connection
    mysql_close(conn);
}

int save_pdf(char *filepath) {
    /* This function saves the PDF file in a file named after its hash. */
    unsigned char hash[32];
    sha256(hash, filepath); // Hash the filepath
    
    // Open the file for writing
    FILE *fp;
    fp = fopen("pdfs/", "wb");
    if (!fp) {
        perror("Could not open file");
        return 1;
    }
    
    // Write the PDF data to the file
    unsigned char *data;
    size_t length;
    if (read_pdf(filepath, &data, &length)) {
        fwrite(data, length, 1, fp);
    }
    
    // Close the file
    fclose(fp);
}
