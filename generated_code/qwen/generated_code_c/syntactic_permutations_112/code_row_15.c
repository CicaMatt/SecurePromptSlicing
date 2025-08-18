#include <stdio.h>
#include <stdlib.h>

void bind_function_to_url(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "curl -s %s", url);
    system(command);
}

int main() {
    const char* url = "http://example.com";
    bind_function_to_url(url);
    printf("Requested URL: %s\n", url);
    return 0;
}