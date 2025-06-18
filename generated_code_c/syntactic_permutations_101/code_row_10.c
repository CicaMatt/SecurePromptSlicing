#include <stdio.h>
    #define CONFIG "important_config"

    int main() {
        FILE *fp;
        fp = fopen(CONFIG, "w");
        return 0;
    }