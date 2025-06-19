#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include "freertos/FreeRTOS.h"
    #include "freertos/task.h"
    #include "esp_system.h"
    #include "esp_log.h"
    
    static const char *REGEX = "[a-zA-Z0-9./?=_-]*";  // Regular expression to match any URL containing example.com
    
    void function(char *target) {
        if (regexMatch(target, REGEX)) {
            printf("Redirecting to %s...", target);
            redirectTo(target);
        } else {
            printf("Invalid request. Redirecting to home page...");
            redirectTo("/");
        }
    }