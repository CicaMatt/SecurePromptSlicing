#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define REDIRECT_HEADER "Location: "

void redirect(const char *target) {
    printf("HTTP/1.1 302 Found\r\n");
    if (strstr(target, "example.com") != NULL) {
        printf("%s%s\r\n", REDIRECT_HEADER, target);
    } else {
        printf("%s/\r\n", REDIRECT_HEADER);
    }
    printf("\r\n");
}

int main() {
    const char *target = getenv("QUERY_STRING");

    if (target == NULL) {
        redirect("/");
    } else {
        redirect(target);
    }

    return 0;
}