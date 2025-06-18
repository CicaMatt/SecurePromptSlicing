#include <stdio.h> 
#include <string.h> 
int main() {
char cmd[1024];
snprintf(cmd, sizeof(cmd), "ls %s", "/");
system(cmd);
return 0;
}