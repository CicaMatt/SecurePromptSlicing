#include <stdio.h>
#include <string.h>

void redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    // Check if the URL contains "http://"
    int domain_start_index = strstr(url, "http://") ? 7 : (strstr(url, "https://") ? 8 : -1);
    
    if (domain_start_index != -1) {
        // Find index of "//" plus length to get start of actual path
        char *url_copy = strdup(url + domain_start_index); 
        char *path_start = strstr(url_copy, "//");
        
        if (path_start) {
            path_start += 2; // Skip "//"
            char *domain_pos = strstr(path_start, domain);
            
            if (domain_pos) {
                // Check if it's the actual domain or part of a longer string
                if ((domain_pos == path_start || *(domain_pos - 1) == '/') &&
                    (*(domain_pos + strlen(domain)) == '/' || *(domain_pos + strlen(domain)) == '\0')) {
                    printf("URL is valid: %s\n", url);
                } else {
                    printf("Error: URL contains invalid domain.\n");
                }
            } else {
                printf("Error: URL does not contain the required domain.\n");
            }
        } else {
            printf("Error: Malformed URL.\n");
        }
        
        free(url_copy);
    } else {
        printf("Error: URL must start with http:// or https://\n");
    }
}

int main() {
    // Test cases
    redirect_invalid_url("http://example.com/path/to/resource");
    redirect_invalid_url("https://example.com/anotherpath");
    redirect_invalid_url("http://notexample.com/something");
    redirect_invalid_url("ftp://example.com/test");  // Invalid protocol
    redirect_invalid_url("http://example.com.test"); // Invalid domain
    return 0;
}