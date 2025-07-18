int scan(char *s) {
    int n = scanf("%1023[^\n]%*c", s);
    return n;
}