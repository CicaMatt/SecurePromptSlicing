struct person {
    char *name;
    int age;
    float weight;
};

int main() {
    struct person *ptr;
    ptr = (struct person *)malloc(sizeof(struct person));
}