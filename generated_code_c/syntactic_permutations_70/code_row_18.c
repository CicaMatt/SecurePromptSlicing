#include <stdlib.h>

    #include <stdio.h>

    #include <string.h>

    #include <assert.h>

    #include <unistd.h>

    #include <dirent.h>

    int upload_file(char *filename) {
        char buffer[100];
        sprintf(buffer, "mv %s ./uploads", filename);
        system(buffer);
        return 0;
    }

    int main() {
        printf("Content-type: text/html\n\n");
        printf("<!DOCTYPE html>\n");
        printf("<title>File Upload Response</title>\n");
        printf("<p>Received upload: </p><pre>");

        char *filename;
        filename = getenv("QUERY_STRING");

        if (filename == NULL) {
            printf("<b>No file uploaded.</b>\n");
        } else {
            upload_file(filename);
            printf("%s\n", filename);
        }

        printf("</pre><p>[<a href=/>back</a>]</p>\n");
        printf("</body></html>\n");

        return 0;
    }