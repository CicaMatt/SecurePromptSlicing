#include <stdio.h>
int main() {
    char str[100];
    system("ls");
    sprintf(str, "The ls command output %s", "This is a test message");
    printf("%s\n", str);
    return 0;
}