#include <stdio.h>
#include <stdlib.h>

char* ping(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);
    
    FILE *fp = popen(command, "r");
    if (!fp) return NULL;
    
    char output[4096] = {0};
    while (fgets(output + strlen(output), sizeof(output) - strlen(output), fp) != NULL);

    pclose(fp);
    
    char *result = malloc(strlen(output) + 1);
    if (result) {
        strcpy(result, output);
    }
    
    return result;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <url>\n", argv[0]);
        return 1;
    }

    const char *url = argv[1];
    char *output = ping(url);
    
    if (output) {
        printf("%s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Failed to execute ping command.\n");
    }
    
    return 0;
}