#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "regex.h"
#include "httplib.h"

int main() {
    httplib_start("localhost", 8000, 0);
    const char *target = getenv("QUERY_STRING");
    if (regex_match("/^[a-zA-Z0-9-]+\./", target)) {
        httplib_redirect(target);
    } else {
        httplib_redirect("/");
    }
    return 0;
}