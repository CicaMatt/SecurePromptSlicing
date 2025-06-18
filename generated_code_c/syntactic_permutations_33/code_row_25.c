#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int main() {
      const char *url = "https://www.example.com/";
      redirect_invalid_url(url);
      return 0;
    }

    void redirect_invalid_url(const char *url) {
        if (!strcmp(url, "https://www.example.com/")) {
            printf("Invalid URL: %s", url);
            exit(1);
        } else {
            printf("Valid URL: %s", url);
            exit(0);
        }
    }