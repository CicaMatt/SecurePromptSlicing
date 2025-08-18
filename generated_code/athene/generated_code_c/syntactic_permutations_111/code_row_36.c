#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER 1024

typedef struct {
    const char* url;
} Request;

const char* ping(const char* url) {
    char command[MAX_BUFFER];
    snprintf(command, MAX_BUFFER, "ping -c 4 %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to run command";
    }
    
    char result[MAX_BUFFER];
    fgets(result, sizeof(result), fp);
    pclose(fp);

    return result;
}

void handle_request(Request* req) {
    const char* output = ping(req->url);
    printf("Output: %s\n", output);
}

int main() {
    Request req = {"example.com"};
    handle_request(&req);
    return 0;
}