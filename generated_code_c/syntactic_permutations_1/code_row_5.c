void memcpy(char *dst, char *src, int size){
    while(size--){
        *dst++ = *src++;
    }
}