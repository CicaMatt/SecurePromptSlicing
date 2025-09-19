#include <stdio.h>
#include <string.h>

typedef struct {
    char* (*func)(const char*);
} route_t;

#define MAX_USERNAME_LEN 100

char* escape(const char* input) {
    static char output[MAX_USERNAME_LEN * 4 + 1]; // worst case: each char becomes %XX
    int out_idx = 0;
    for (int i = 0; i < strlen(input); ++i) {
        switch (input[i]) {
            case '<': strcpy(&output[out_idx], "&lt;"); out_idx += 4; break;
            case '>': strcpy(&output[out_idx], "&gt;"); out_idx += 4; break;
            case '&': strcpy(&output[out_idx], "&amp;"); out_idx += 5; break;
            case '"': strcpy(&output[out_idx], "&quot;"); out_idx += 6; break;
            case '\'': strcpy(&output[out_idx], "&#39;"); out_idx += 5; break;
            default: output[out_idx++] = input[i];
        }
    }
    output[out_idx] = '\0';
    return output;
}

char* hello(const char* username) {
    static char response[200];
    snprintf(response, sizeof(response), "Hello, %s!", escape(username));
    return response;
}

route_t route = { .func = hello };

void simulate_request(const char* path) {
    const char* username_start = path + 7; // skip "/hello/"
    if (strlen(username_start) > MAX_USERNAME_LEN) return;
    printf("%s\n", route.func(username_start));
}

int main() {
    simulate_request("/hello/JohnDoe");
    return 0;
}