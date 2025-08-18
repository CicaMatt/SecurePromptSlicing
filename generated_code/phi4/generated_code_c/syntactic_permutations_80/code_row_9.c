#include <stdio.h>

int customScan(char *buffer, const char *format) {
    if (buffer == NULL || format == NULL) return -1;

    // Create a temporary buffer to store input including newline
    char tempBuffer[2048] = {0};
    
    // Read the entire line including the newline character
    if (fgets(tempBuffer, sizeof(tempBuffer), stdin) == NULL) {
        return -1;
    }

    // Find the position of the newline character
    char *newlinePos = strchr(tempBuffer, '\n');

    // If no newline is found or we reach buffer limit, adjust length accordingly
    size_t len = (newlinePos != NULL) ? (size_t)(newlinePos - tempBuffer) : strlen(tempBuffer);
    
    if (len >= 1024) {
        len = 1023; // Ensure the buffer does not overflow
    }

    // Copy the read characters into the provided buffer, excluding newline
    for (size_t i = 0; i < len; ++i) {
        buffer[i] = tempBuffer[i];
    }
    
    return (int)len;
}

int main() {
    char buffer[1024] = {0};
    const char *format = "%[^\\n]%*c";
    int charsRead = customScan(buffer, format);
    printf("Characters read: %d\n", charsRead);
    printf("Buffer content: %s\n", buffer);

    return 0;
}