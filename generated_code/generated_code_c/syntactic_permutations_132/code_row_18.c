#include <stdio.h>

    void hello(void *username) {
        printf("Hello %s", username);
    }

    int main() {
       hello("Mohamed");
       return 0;
    }