//upload_pdf_file.c
    
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/types.h>
    #include <unistd.h>
    #include <errno.h>
    #include <sys/stat.h>
    
    int main(int argc, char *argv[])
    {
        //check if the command line arguments are correct
        if (argc != 2)
        {
            printf("Usage: %s <path/to/pdf/file>\n", argv[0]);
            return 1;
        }
    
        //open the pdf file
        FILE *pdf_file = fopen(argv[1], "r");
        if (pdf_file == NULL)
        {
            printf("Error: could not open %s\n", argv[1]);
            return 1;
        }
    
        //get the file size
        fseek(pdf_file, 0L, SEEK_END);
        int file_size = ftell(pdf_file);
        fseek(pdf_file, 0L, SEEK_SET);
    
        //allocate memory for the file content
        char *pdf_content = (char *)malloc(sizeof(char) * file_size);
        if (pdf_content == NULL)
        {
            printf("Error: could not allocate memory\n");
            return 1;
        }
    
        //read the pdf file content
        int read_bytes = fread(pdf_content, sizeof(char), file_size, pdf_file);
        if (read_bytes != file_size)
        {
            printf("Error: could not read %s\n", argv[1]);
            return 1;
        }
    
        //close the pdf file
        fclose(pdf_file);
    
        //create a new directory for the uploaded files
        char *uploads_dir = "./uploads";
        int status = mkdir(uploads_dir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        if (status != 0 && errno != EEXIST)
        {
            printf("Error: could not create directory %s\n", uploads_dir);
            return 1;
        }
    
        //create a new file in the uploads directory
        char *uploaded_file = "./uploads/";
        strcat(uploaded_file, argv[1]);
        FILE *uploaded_pdf_file = fopen(uploaded_file, "w");
        if (uploaded_pdf_file == NULL)
        {
            printf("Error: could not open %s\n", uploaded_file);
            return 1;
        }
    
        //write the pdf file content to the new file
        int write_bytes = fwrite(pdf_content, sizeof(char), file_size, uploaded_pdf_file);
        if (write_bytes != file_size)
        {
            printf("Error: could not write %s\n", uploaded_file);
            return 1;
        }
    
        //close the new file
        fclose(uploaded_pdf_file);
    
        //free allocated memory
        free(pdf_content);
    
        //success
        printf("Success: %s has been uploaded to %s\n", argv[1], uploads_dir);
        return 0;
    }