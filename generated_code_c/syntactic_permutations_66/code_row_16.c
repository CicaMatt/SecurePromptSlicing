#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main()
{
    printf("Content-type:text/html\r\n\r\n");

    char *save_folder = "path to folder";
    char file_name[30];

    FILE *fptr;

    if(strcmp(getenv("REQUEST_METHOD"),"POST")==0)
    {
        printf("<html><body>");
        fptr = fopen("/tmp/file.pdf","wb");
        while(1)
        {
            char *content_length = getenv("CONTENT_LENGTH");
            int i,j;

            if(content_length == NULL)
            {
                break;
            }

            j=atoi(content_length);

            for(i=0;i<j;i++)
            {
                char c = fgetc(stdin);
                fputc(c,fptr);
            }
        }
        printf("File Saved Successfully!");
        fclose(fptr);
    }
    else
    {
        printf("<form action=# method='post' enctype='multipart/form-data'>\n");
        printf("Select a file to upload : ");
        printf("<input type='file' name='file' /><br /><br />");
        printf("<input type='submit' value='Upload!' /></form>");
    }

    return 0;
}