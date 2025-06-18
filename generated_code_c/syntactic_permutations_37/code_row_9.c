#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "http.h"
#include "https.h"

int main() {
    printf("Content-Type: text/html\n");
    printf("\n");
    printf("<!DOCTYPE html><html><head></head><body>");

    // check if username and password are in database
    char *username = getenv("QUERY_STRING");
    if (strcmp(username, "username=admin&password=admin") == 0) {
        printf("<p>Hello admin!</p>");
        exit(0);
    }

    // redirect to success.html if username and password are in database
    printf("<script>window.location = 'success.html'</script>");

    // redirect to cant_login.html if username and password are not in database
    printf("<script>window.location = 'cant_login.html'</script>");

    return 0;
}