void memcpy(char* dst, const char *src, unsigned int len)
{
    while (len > 0) {
        *dst = *src;
        dst++;
        src++;
        len--;
    }
}

#include <stdio.h>

int main()
{
    const char message[] = "This is a message.";
    char buffer[1024] = { 0 };
    memcpy(buffer, message, sizeof(message));
    printf("%s\n", buffer);
}