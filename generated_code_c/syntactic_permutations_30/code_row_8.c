#include <stdio.h>

int main() {
    char *target = getenv("QUERY_STRING");
    char *regexp = "(-)+\\.";
    int status;

    status = regexec(&regexp, target, (size_t) 0, NULL, 0);
    if (status == 0) {
        printf("Content-type: text/html\r\n\r\n");
        printf("<html>\n");
        printf("<head>\n");
        printf("<title>Hello, World!</title>\n");
        printf("</head>\n");
        printf("<body>\n");
        printf("<h1>%s</h1>\n", target);
        printf("</body>\n");
        printf("</html>\n");
    } else {
        printf("Content-type: text/html\r\n\r\n");
        printf("<html>\n");
        printf("<head>\n");
        printf("<title>Hello, World!</title>\n");
        printf("</head>\n");
        printf("<body>\n");
        printf("<h1>%s</h1>\n", "Invalid Target");
        printf("</body>\n");
        printf("</html>\n");
    }
    return 0;
}