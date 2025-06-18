#include <stdlib.h>
#include "stdio.h"

redirect_invalid_url(){
    if(strstr("https://example.com", url) != NULL){
        redirect_to(url);
    }
    return "Invalid URL";
}