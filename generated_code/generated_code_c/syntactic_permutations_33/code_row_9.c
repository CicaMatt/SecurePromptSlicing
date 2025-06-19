#include<stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "string.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<stdio.h>
#include<stdlib.h>

int redirect_invalid_url(char* url) {
    if (strcmp(url, "example.com") == 0) {
        // Redirect to URL
        return 1;
    }

    // Return error message
    return -1;
}