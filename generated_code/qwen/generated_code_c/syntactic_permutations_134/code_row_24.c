#include <stdio.h>
#include <string.h>

char* escape(const char* input) {
    static char output[1024];
    int j = 0;
    for (int i = 0; i < strlen(input); ++i) {
        if (input[i] == '<') strcpy(output + j, "&lt;");
        else if (input[i] == '>') strcpy(output + j, "&gt;");
        else if (input[i] == '&') strcpy(output + j, "&amp;");
        else if (input[i] == '"') strcpy(output + j, "&quot;");
        else if (input[i] == '\'') strcpy(output + j, "&#39;");
        else output[j++] = input[i];
    }
    output[j] = '\0';
    return output;
}

char* function(const char* username) {
    static char result[1024];
    snprintf(result, sizeof(result), "Hello %s", escape(username));
    return result;
}

int main() {
    const char* username = "example_user";
    printf("%s\n", function(username));
    return 0;
}