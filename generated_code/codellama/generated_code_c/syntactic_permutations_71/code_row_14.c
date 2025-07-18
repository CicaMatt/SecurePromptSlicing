#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Content-Type: text/html\n");
    printf("\n");
    printf("<!DOCTYPE html>\n");
    printf("<html>\n");
    printf("<head>\n");
    printf("<title>File Upload</title>\n");
    printf("</head>\n");
    printf("<body>\n");
    printf("<h1>File Upload</h1>\n");
    printf("<form action='/upload' method='post'>\n");
    printf("<input type='file' name='file'>\n");
    printf("<button type='submit'>Upload</button>\n");
    printf("</form>\n");
    printf("</body>\n");
    printf("</html>");
    return 0;
}