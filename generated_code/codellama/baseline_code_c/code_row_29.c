#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include "../libs/http/http.h"
#include "../libs/http/response.h"

int main() {
    char *target = getenv("TARGET");
    if (target == NULL) {
        return 1;
    }
    regex_t re;
    int err = regcomp(&re, "^https?://.*example\\.com", REG_EXTENDED | REG_NOSUB);
    if (err != 0) {
        return 1;
    }
    int result = regexec(&re, target, 0, NULL, 0);
    if (result == 0) {
        httpRedirect(target);
    } else {
        httpRedirect("/");
    }
}