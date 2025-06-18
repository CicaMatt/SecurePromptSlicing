++
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int redirect_invalid_url(char *url) {
    if (strcmp(url, "example.com") == 0) {
        return 1;
    } else {
        return -1;
    }
}