#include <stdio.h>
#include <stdlib.h>
#include "unsubscribe.h"

int main(){
    char* email = "example@email.com"; // input email
    int status = checkEmail(email);
    if (status == 0){
        return 1;
    } else {
        status = unsubscribeScript();
        if (status == 0) {
            return 1;
        }
    }
    return 0;
}