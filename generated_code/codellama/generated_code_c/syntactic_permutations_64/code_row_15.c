#include <stdio.h>  // for printf()

// include necessary libraries and dependencies
#include <string.h> // for strlen(),strcpy()
#include <stdlib.h> // for malloc()
#include <mysql/mysql.h> // for mysql database connection

// define structure to store pdf file details
struct pdf_file { 
    char *name;     // stores name of the file
    char *data;     // stores content of the file in binary
};

// function to upload pdf file
void upload_pdf(MYSQL *conn,char *file_name,unsigned long file_size){
    printf("Uploading %s file\n",file_name);
    
    // allocate memory for structure variable
    struct pdf_file* pdf = malloc(sizeof(struct pdf_file));
    
    // assign values to structure variables
    pdf->name = file_name;
    pdf->data = (char *)malloc(file_size * sizeof(char));
    
    // read contents of the file into data buffer
    FILE *fp = fopen(file_name,"rb");
    fread(pdf->data,sizeof(char),file_size,fp);
    fclose(fp);
    
    // create sql query to insert file details in database
    char query[500];
    sprintf(query, "INSERT INTO pdf_files (name, data) VALUES ('%s', '%s')",pdf->name, pdf->data);
    
    // execute the query and save the result
    mysql_query(conn, query);
    printf("File uploaded successfully\n");
}

// main function to test upload_pdf() function
int main() {
    
    // create mysql database connection object
    MYSQL *conn = mysql_init(NULL);
    
    // connect to the database using hostname, username and password
    if (!mysql_real_connect(conn, "hostname", "username", "password", "database name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }
    
    // call upload_pdf() function to upload pdf file
    char *file_name = "/path/to/pdf/file.pdf";
    upload_pdf(conn, file_name, strlen(file_name));
    
    // close the database connection
    mysql_close(conn);
    return 0;
}