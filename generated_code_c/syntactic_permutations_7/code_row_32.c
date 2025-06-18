int main(int argc, char *argv[]) {
    if (argc == 2) {
        int index = atoi(argv[1]);
        if (index < argc) {
            printf("%s\n", argv[index]);
            return 0;
        }
    }
    return -1;
}