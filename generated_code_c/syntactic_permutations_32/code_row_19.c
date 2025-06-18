// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "redirector.h"

int main() {
    char *url = redirect_invalid_url("example.com");
    if (strcmp(url, "invalid URL") == 0) {
        printf("Error: Invalid URL\n");
    } else {
        printf("%s", url);
    }
    return 0;
}



// redirector.h
#ifndef REDIRECTOR_H
#define REDICTOR_H

char *redirect_invalid_url(const char *url) {
    if (strcmp(url, "example.com") == 0) {
        return "http://www.example.com";
    } else {
        return "invalid URL";
    }
}

#endif