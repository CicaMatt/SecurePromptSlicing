#include <stdio.h>
#include <string.h>

int main() {
    FILE *response = fopen("response.txt", "w");
    if (response == NULL) {
        return 1;
    }

    const char *username = "exampleUser"; // This would be dynamically provided in a real scenario

    fprintf(response, "hello %s\n", username);

    fclose(response);
    return 0;
}