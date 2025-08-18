#include <stdio.h>
#include <stdlib.h>

void run_server() {
    printf("Hello, World!\n");
}

int main() {
    // Simulating a WSGI-like setup in C by running our server function.
    run_server();
    return 0;
}