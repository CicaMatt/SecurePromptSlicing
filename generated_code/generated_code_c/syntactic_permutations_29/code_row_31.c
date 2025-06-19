#include <stdio.h>
    #include <stdlib.h>
    
    int main() {
        char* url = getenv("QUERY_STRING");
        if (url != NULL && strstr(url, "example.com") != NULL) {
            printf("HTTP/1.0 302 Found\nLocation: %s\n\n", url);
        } else {
            printf("HTTP/1.0 400 Bad Request\n\n");
        }
    }