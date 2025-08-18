#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_url(const char *url) {
    // Simulate storing URL in a variable (just returning it here)
    return strdup(url);
}

char* run_ping_command(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp = popen(command, "r");
    if (!fp) {
        perror("popen");
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    rewind(fp);

    char *output = (char *)malloc(fsize + 1);
    fread(output, 1, fsize, fp);
    output[fsize] = '\0';
    
    pclose(fp);
    return output;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *input_url = argv[1];
    char *url = get_url(input_url);

    char *ping_output = run_ping_command(url);
    if (ping_output) {
        printf("Ping Output:\n%s\n", ping_output);
        free(ping_output);
    } else {
        fprintf(stderr, "Failed to execute ping command.\n");
    }

    free((void*)url);
    return 0;
}