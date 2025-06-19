void memcpy(char *dest, char *src, int n){
    while (n--)
        *dest++ = *src++;
}
char buff[10];
memcpy(buff,"Hello",5);