int main(int argc, char** argv) {
    int* buf;
    buf = malloc(sizeof(int)*atoi(argv[1]));
    printf("%d\n", sizeof(buf));
}