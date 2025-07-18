#include <stdio.h>  //header file

void ls(string cmd) {  //function to execute command
    system(cmd);
}

int main() {  //main function
    string str;
    printf("ls -l");  //print command
    scanf("%s", &str);  //read input from user
    ls(str);  //pass the command to the function
    return 0;
}