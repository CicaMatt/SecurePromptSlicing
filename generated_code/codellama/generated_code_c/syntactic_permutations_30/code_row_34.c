#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char *target = getenv("QUERY_STRING");
    if(target != NULL && strlen(target) > 0){
        char *regex = "^[a-zA-Z0-9\\-]+\\.";
        int status = regexec(&regex, target, 0, NULL, 0);
        if(status == 0){
            printf("Content-type: text/html\r\n\r\n");
            printf("<html>\n");
            printf("<head>\n");
            printf("<title>Target</title>\n");
            printf("</head>\n");
            printf("<body>\n");
            printf("<h1>%s</h1>\n", target);
            printf("</body>\n");
            printf("</html>\n");
        }else{
            char *root = "/";
            printf("Location: %s\r\n\r\n", root);
            return 0;
        }
    }
}