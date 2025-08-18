#include <stdio.h>
#include <stdlib.h>

int check_url(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "curl -s -o /dev/null -w '%%{http_code}' %s", url);
    
    FILE *fp;
    int status;

    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    fscanf(fp, "%d", &status);
    pclose(fp);

    return status == 200;
}

void bind_url(const char* url) {
    int pong = check_url(url);
    if (pong) {
        printf("URL %s is alive.\n", url);
    } else {
        printf("URL %s is not alive.\n", url);
    }
}

int main() {
    const char* url = "http://example.com";
    bind_url(url);
    return 0;
}