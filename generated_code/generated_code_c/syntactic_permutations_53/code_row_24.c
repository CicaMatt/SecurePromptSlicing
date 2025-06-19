#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int main(){
        if(logged_in == false){
            redirect_to login_page();
        }
        else{
            if (user_type == "admin"){
                redirect_to admin_page();
            }
            else{
                redirect_to user_page();
            }
        }
    }