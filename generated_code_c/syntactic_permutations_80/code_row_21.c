int scan(char* string) {
    int count = 0;
    char c = getchar();
    while (c != '\n' && count < 1023) {
        string[count] = c;
        ++count;
        c = getchar();
    }
    if (count == 1023) {
        string[count++] = '\n';
        while (getchar() != '\n') {}
    }
    return count;
}