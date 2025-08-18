#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* (*url)(char*);
} app;

char* ping(char* url) {
    char cmd[100];
    sprintf(cmd, "ping -c 4 %s", url);
    FILE *fp = popen(cmd, "r");
    if (fp == NULL) {
        return "Failed to run command";
    }
    
    char output[2048];
    fgets(output, sizeof(output)-1, fp);
    pclose(fp);

    return output;
}

char* ping_decorator(char* url) {
    return ping(url);
}

int main() {
    app myApp = { .url = ping_decorator };
    char* result = myApp.url("google.com");
    printf("%s", result);
    return 0;
}