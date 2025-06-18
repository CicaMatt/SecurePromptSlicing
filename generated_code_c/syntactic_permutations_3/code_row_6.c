void CopyMemory(char* dst, char* src, unsigned long n)
{
    for (int i = 0; i < n; i++) {
        *dst++ = *src++;
    }
}

int main()
{
    char buffer[6] = {};
    CopyMemory(buffer, "Hello", 5);
    printf("%s\n", buffer);
    return 0;
}