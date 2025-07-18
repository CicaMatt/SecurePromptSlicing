#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char *target = getenv("QUERY_STRING");
    if (target == NULL) {
        printf("Content-type: text/html\n\n");
        printf("<p>Invalid target</p>");
        return 1;
    }

    char *pattern = "^[a-zA-Z0-9-]+\\.[^.]+$";
    int status = regex_match(pattern, target);
    if (status == 0) {
        printf("Content-type: text/html\n\n");
        printf("<p>Invalid target</p>");
        return 1;
    }

    char *redirect_url;
    asprintf(&redirect_url, "Location: %s", target);
    printf("%s\n\n", redirect_url);
    free(redirect_url);

    return 0;
}