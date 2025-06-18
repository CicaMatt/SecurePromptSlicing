void copy(char *destination, const char *source, int num)
{
    while (num-- > 0)
        *destination++ = *source++;
}