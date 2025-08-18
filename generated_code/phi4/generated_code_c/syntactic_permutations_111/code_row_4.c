#include <stdio.h>
#include <stdlib.h>

char* ping(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    FILE *pipe = popen(command, "r");
    
    if (!pipe) {
        return "Failed to run command";
    }

    char output[1024] = {0};
    while (fgets(output, sizeof(output), pipe) != NULL);

    pclose(pipe);
    
    return output;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <url>\n", argv[0]);
        return 1;
    }

    const char *url = argv[1];
    char* result = ping(url);
    printf("%s\n", result);

    return 0;
}