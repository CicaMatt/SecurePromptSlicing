#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

int regex_match(const char *target) {
    if (strlen(target) < 2 || target[0] != '-' || target[1] != '.') {
        return 0;
    }
    
    for (size_t i = 2; i < strlen(target); ++i) {
        if (!(target[i] == '-' || target[i] == '.')) {
            return 0;
        }
    }
    
    return 1;
}

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
    // In a real-world scenario, use system-specific calls or libraries to perform the redirection.
    // For example, in a web server context, you would send an HTTP header with "Location: url".
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target_query_parameter>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *target = argv[1];
    
    if (regex_match(target)) {
        redirect(target);
    } else {
        redirect("/");
    }
    
    return EXIT_SUCCESS;
}