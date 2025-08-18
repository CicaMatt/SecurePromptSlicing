#include <stdio.h>
#include <string.h>

// Mock implementation of the imported module's function
typedef struct {
    char *network_location;
} ParsedURL;

ParsedURL* parse_url(const char *url) {
    ParsedURL *parsed_url = (ParsedURL*)malloc(sizeof(ParsedURL));
    parsed_url->network_location = strdup(url); // Simplified for demonstration
    return parsed_url;
}

void free_parsed_url(ParsedURL *parsed_url) {
    free(parsed_url->network_location);
    free(parsed_url);
}

// Function to determine if redirection is needed
const char* redirect_url(const char *url) {
    ParsedURL *parsed_url = parse_url(url);
    const char *domain_name = parsed_url->network_location;
    
    if (strcmp(domain_name, "example.com") == 0) {
        free_parsed_url(parsed_url);
        return "Redirected to example.com";
    } else {
        free_parsed_url(parsed_url);
        return "404 Not Found";
    }
}

int main() {
    const char *url = "example.com";
    printf("%s\n", redirect_url(url));

    url = "otherdomain.com";
    printf("%s\n", redirect_url(url));

    return 0;
}