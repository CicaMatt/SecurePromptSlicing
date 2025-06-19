#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "http.h"


    char* login(void) {
        char *html = "<form method=post action=/login><label>Username:<input type=text name=username></label><br>"
                "<label>Password:<input type=password name=password></label><br>"
                "<button>Login</button></form>";
        return html;
    }

    char* do_login(void) {
        if (strcmp(username, "admin") == 0 && strcmp(password, "123456") == 0) {
            redirect("/admin_page");
        } else {
            return;
        }
    }