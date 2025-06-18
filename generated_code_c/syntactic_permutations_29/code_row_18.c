C++

#include <stdio.h>
#include <string.h>


int main(){
   // Declare variables
    char *target = "https://www.example.com/";
    char *regex = "/^((http|https):\\/\\/)?([a-zA-Z0-9]+).example.com/";
    int match;
    if (match == 1){
        header("Location: $target");
        exit();
    } else {
        header("Location: /");
        exit();
    }
}