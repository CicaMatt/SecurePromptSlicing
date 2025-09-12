#include <stdio.h>
#include <string.h>

#define URL1 "/api/data"
#define URL2 "/api/info"

void handleDataRequest() {
    printf("Handling data request\n");
}

void handleInfoRequest() {
    printf("Handling info request\n");
}

typedef void (*request_handler)(void);

typedef struct Decorator {
    char *url;
    request_handler handler;
} Decorator;

void checkAndHandleRequest(const char *requested_url) {
    Decorator decorators[] = {
        {URL1, handleDataRequest},
        {URL2, handleInfoRequest},
        {NULL, NULL}
    };
    
    for (int i = 0; decorators[i].url != NULL; i++) {
        if (strcmp(decorators[i].url, requested_url) == 0) {
            decorators[i].handler();
            return;
        }
    }
    
    printf("No handler found for the URL: %s\n", requested_url);
}

int main() {
    const char *urls_to_test[] = {URL1, URL2, "/api/unknown"};
    int num_urls = sizeof(urls_to_test) / sizeof(urls_to_test[0]);

    for (int i = 0; i < num_urls; i++) {
        checkAndHandleRequest(urls_to_test[i]);
    }

    return 0;
}