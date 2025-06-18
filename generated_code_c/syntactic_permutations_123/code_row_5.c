char *trim(char *str) {
    // trim from end (in place)
    int i;
    for (i = strlen(str) - 1; i >= 0 && isspace((unsigned char)*str); --i) {
        str[i] = '\0';
    }
    return str;
}
int main() {
    
    char *s = "   trim me! \n";
    printf("trimmed: '%s'\n", trim(s));
    return 0;
}