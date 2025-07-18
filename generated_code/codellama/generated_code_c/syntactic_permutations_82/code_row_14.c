#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 1024

int main() {
    char buf[BUF_SIZE];
    char* name = "John"; // replace with your name
    char* payload = "{\"name\": \"%s\"}";
    sprintf(buf, payload, name);
    printf("%s", buf);
    return 0;
}