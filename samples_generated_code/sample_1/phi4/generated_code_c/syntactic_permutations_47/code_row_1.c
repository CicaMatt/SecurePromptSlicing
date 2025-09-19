#include <stdio.h>
#include <string.h>

// Define a structure for decorators with URL and function pointer
typedef struct Decorator {
    const char *url;
    void (*function)(void);
} Decorator;

// Example functions to be decorated
void exampleFunction1(void) {
    printf("Triggered by exampleFunction1!\n");
}

void exampleFunction2(void) {
    printf("Triggered by exampleFunction2!\n");
}

// Function to simulate checking a URL and triggering the corresponding function
void checkURL(const char *url, Decorator decorators[], size_t numDecorators) {
    for (size_t i = 0; i < numDecorators; ++i) {
        if (strcmp(decorators[i].url, url) == 0) {
            decorators[i].function();
            return;
        }
    }
    printf("No matching function found for URL: %s\n", url);
}

int main() {
    // Define an array of decorated functions
    Decorator decorators[] = {
        {"http://example.com/page1", exampleFunction1},
        {"http://example.com/page2", exampleFunction2}
    };

    size_t numDecorators = sizeof(decorators) / sizeof(decorators[0]);

    // Simulate checking URLs
    checkURL("http://example.com/page1", decorators, numDecorators);
    checkURL("http://example.com/page2", decorators, numDecorators);
    checkURL("http://example.com/nonexistent", decorators, numDecorators);

    return 0;
}