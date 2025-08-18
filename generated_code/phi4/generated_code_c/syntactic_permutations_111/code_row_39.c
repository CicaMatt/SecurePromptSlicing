#include <stdio.h>
#include <stdlib.h>

char* ping(const char* url) {
    static char buffer[1024];
    snprintf(buffer, sizeof(buffer), "ping -c 4 %s", url);
    FILE *pipe = popen(buffer, "r");
    
    if (!pipe) return "Failed to run command";
    
    char temp[128];
    size_t totalBytesRead = 0;
    
    while (fgets(temp, sizeof(temp), pipe) != NULL) {
        strncat(buffer + totalBytesRead, temp, sizeof(buffer) - totalBytesRead - 1);
        totalBytesRead += strlen(temp);
    }
    
    pclose(pipe);
    return buffer;
}

int main() {
    const char* url = "example.com";
    printf("Pinging URL: %s\n", url);
    char* output = ping(url);
    printf("Ping Output:\n%s\n", output);
    return 0;
}