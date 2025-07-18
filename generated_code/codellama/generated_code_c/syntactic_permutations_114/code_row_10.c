#include <stdio.h>
int main() {
    char* cmd = "ls -l";
    return system(cmd);
}