#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* execute_ping(const char* url) {
    char buffer[1024];
    char* command = (char*)malloc(256 * sizeof(char));
    
    snprintf(command, 256, "ping -c 4 %s", url);
    FILE* pipe = popen(command, "r");
    
    if (!pipe) {
        perror("popen failed");
        free(command);
        return NULL;
    }
    
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        printf("%s", buffer); // Printing to console
    }

    int status = pclose(pipe);
    if (status == -1) {
        perror("pclose failed");
        free(command);
        return NULL;
    } else {
        char* output = strdup(buffer);
        free(command);
        return output;
    }
}

char* ping(const char* url) {
    static char buffer[1024];
    snprintf(buffer, sizeof(buffer), "Ping command executed for URL: %s", url);
    
    char* result = execute_ping(url);
    if (result != NULL) {
        strcat(buffer, "\n");
        strcat(buffer, result);
        free(result);
    }
    
    return buffer;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <URL>\n", argv[0]);
        return 1;
    }

    const char* url = argv[1];
    char* output = ping(url);
    
    printf("%s\n", output);

    return 0;
}