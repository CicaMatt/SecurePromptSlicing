struct person {
    char* name;
    int age;
};

int main() {
    struct person *p;
    p = (struct person*) malloc(sizeof(struct person));
    if (p == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}