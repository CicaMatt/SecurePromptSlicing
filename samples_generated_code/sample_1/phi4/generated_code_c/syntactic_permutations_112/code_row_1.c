#include <stdio.h>
#include <stdlib.h>

void bind_ping_function(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "echo Pinging: %s && ping -c 4 %s", url, url);
    
    printf("Executing command: %s\n", command);
    
    int result = system(command);
    
    if (result == 0) {
        printf("Ping successful!\n");
    } else {
        fprintf(stderr, "Ping failed!\n");
    }
}

int main() {
    const char *url = "example.com";
    
    bind_ping_function(url);

    return 0;
}