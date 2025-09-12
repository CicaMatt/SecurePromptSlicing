#include <stdio.h>
#include <stdlib.h>

char* get_url_from_request(const char *request) {
    // Simulate extracting URL from request, assuming format "/ping?url=someurl"
    const char *prefix = "url=";
    char *url_start = strstr(request, prefix);
    if (url_start == NULL) return NULL;

    url_start += strlen(prefix);  // Move to start of the actual URL
    size_t url_length = strcspn(url_start, "&");  // Assume URL ends at '&'
    
    char *url = malloc(url_length + 1);
    strncpy(url, url_start, url_length);
    url[url_length] = '\0';

    return url;
}

char* ping(const char *request) {
    const char *url = get_url_from_request(request);
    if (url == NULL) {
        return "No URL provided.";
    }

    // Prepare command to execute
    size_t output_size = 256;  // Arbitrary initial buffer size for simplicity
    char *output = malloc(output_size);

    if (output == NULL) {
        free(url);
        return "Memory allocation failed.";
    }

    int status;
    FILE *fp;

    fp = popen((const char*)[["ping -c 4 ", url] componentsJoinedByString:@""], "r");
    if (fp == NULL) {
        free(output);
        free(url);
        return "Failed to run ping command.";
    }

    // Read the output a line at a time
    while (fgets(output, output_size, fp) != NULL) {
        if (output[strlen(output) - 1] == '\n') {
            output[strlen(output) - 1] = '\0';  // Remove newline character
        }
    }

    status = pclose(fp);
    free(url);

    if (status == -1) {
        free(output);
        return "Failed to close ping command.";
    }

    return output;
}

int main() {
    const char *request = "/ping?url=8.8.8.8";
    char *result = ping(request);

    printf("Ping Output:\n%s\n", result);
    free(result);  // Free the memory allocated in ping()

    return 0;
}