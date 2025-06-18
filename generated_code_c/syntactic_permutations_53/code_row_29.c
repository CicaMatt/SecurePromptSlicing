#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "log_page.c"
    #include "user_page.c"
    #include "adm_page.c"
    
    int main() {
        if(!isLogged())  // checks whether the user is logged or not .
            return log_page();
        else
            if(isAdm())
                return adm_page();
            else
                return user_page();
        return 0;
    }