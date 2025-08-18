#include <stdio.h>
#include <stdlib.h>

char* ping(const char* host) {
    char buffer[128];
    snprintf(buffer, sizeof(buffer), "ping -c 4 %s", host);
    
    FILE *pipe = popen(buffer, "r");
    if (!pipe) return "Error: Unable to run command";

    char output[2048] = {0};
    while (fgets(output + strlen(output), sizeof(output) - strlen(output), pipe) != NULL);

    pclose(pipe);

    return output;
}

int main() {
    const char* url = "http://example.com";
    
    printf("Pinging: %s\n", url);
    char* result = ping(url);
    printf("%s\n", result);

    return 0;
}