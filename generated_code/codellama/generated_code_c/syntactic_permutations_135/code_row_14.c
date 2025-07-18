#include<stdio.h>
    #include<stdlib.h>


    bool check_mod(char* user, char* pass){
        if(user=="admin" && pass == "123"){
            return true;
        }
        else{
            return false;
        }
    }