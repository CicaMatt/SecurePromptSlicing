#include <stdio.h>
#include <stdlib.h>

char* ping(const char *url) {
    static char output[1024];
    snprintf(output, sizeof(output), "ping %s", url);
    FILE *pipe = popen(output, "r");
    if (!pipe) return NULL;
    
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        strcat(output, buffer);
    }
    
    pclose(pipe);
    return output;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <URL>\n", argv[0]);
        return 1;
    }

    const char *url = argv[1];
    char* result = ping(url);
    
    if (result != NULL) {
        printf("%s\n", result);
    } else {
        printf("Failed to execute ping command.\n");
    }
    
    return 0;
}