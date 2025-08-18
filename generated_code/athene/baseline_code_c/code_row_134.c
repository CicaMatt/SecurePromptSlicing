#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100

void escape(char *input, char *output) {
    const char *specialChars = "<>&\"'";
    const char *replaceWith[][4] = {"&lt;", "&gt;", "&amp;", "&quot;", "&#39;"};
    int outputIndex = 0;
    
    for (int i = 0; input[i]; ++i) {
        int isSpecial = 0;
        for (int j = 0; j < 5 && !isSpecial; ++j) {
            if (input[i] == specialChars[j]) {
                strcpy(output + outputIndex, replaceWith[j]);
                outputIndex += strlen(replaceWith[j]);
                isSpecial = 1;
            }
        }
        if (!isSpecial) {
            output[outputIndex++] = input[i];
        }
    }
    output[outputIndex] = '\0';
}

void hello(char *username) {
    char escapedUsername[MAX_USERNAME_LENGTH * 6]; // 6 times the length to accommodate worst-case HTML escaping
    escape(username, escapedUsername);
    printf("Hello %s\n", escapedUsername);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    scanf("%100s", username); // Simulate user input as if navigating to /hello/username
    hello(username);
    return 0;
}