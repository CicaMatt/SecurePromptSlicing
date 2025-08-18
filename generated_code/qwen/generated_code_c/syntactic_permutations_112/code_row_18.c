#include <stdio.h>
#include <stdlib.h>

void ping() {
    system("ping -c 4 google.com");
}

int main() {
    char *url = "ping";
    if (strcmp(url, "ping") == 0) {
        ping();
    }
    return 0;
}