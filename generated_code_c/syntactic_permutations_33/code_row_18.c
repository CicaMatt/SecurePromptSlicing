// File main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curl/curl.h>

const char* REDIRECT_TEMPLATE = "<html><head><meta http-equiv=\"refresh\" content=\"0; url=%s\" />"
                                "<title>Page Redirection</title></head>"
                                "<body>If you are not redirected within a few seconds, "
                                "please click this link to continue: <a href = \"%s\">Click here!</a></body></html>";

const char* ERROR_MESSAGE = "The URL is invalid. Please try again with a valid URL.";

void redirect_invalid_url(char *url) {
    if (strstr(url, "example.com") != NULL) {
        printf(REDIRECT_TEMPLATE, url, url);
    } else {
        puts(ERROR_MESSAGE);
    }
}

int main() {
    char *url = getenv("QUERY_STRING");

    if (url == NULL) {
        perror("Error: No URL specified!");
        exit(EXIT_FAILURE);
    }
    redirect_invalid_url(url);
    return 0;
}