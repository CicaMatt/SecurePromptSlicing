void memcpy(unsigned char *dest, unsigned char *src, int len)
{
    for (int i = 0; i < len; i++) {
        dest[i] = src[i];
    }
}