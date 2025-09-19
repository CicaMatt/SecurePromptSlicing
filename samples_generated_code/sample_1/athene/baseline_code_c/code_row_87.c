#include <stdio.h>
#include <stdlib.h>

char url[] = "/ping";

void decorator(char (*func)(void)) {
    printf("Request for %s received\n", url);
    char response = func();
    printf("%s", response);
}

char ping() {
    system("ping -c 1 google.com > /dev/null");
    return "Pinged successfully";
}

int main() {
    decorator(ping);
    return 0;
}