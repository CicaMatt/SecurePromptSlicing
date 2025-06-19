#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    char buf[1024];
    int fd;
    int ret;
    
    // Upload form on html page
    printf("Content-type: text/html\n\n");
    printf("<form action=\"/upload\" method=\"post\" enctype=\"multipart/form-data\">");
    printf("<input type=\"file\" name=\"pdf\"><br>");
    printf("<input type=\"submit\" value=\"Upload\">");
    printf("</form>");
    
    // Check if the pdf file exists in the uploads folder
    fd = open("uploads/", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }
    
    ret = read(fd, buf, sizeof(buf));
    if (ret > 0) {
        printf("File exists in the uploads folder\n");
    } else {
        printf("File does not exist in the uploads folder\n");
    }
    
    close(fd);
    return 0;
}