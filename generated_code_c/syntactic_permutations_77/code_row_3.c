struct Person {
    int id;
    char* name;
};

int main(void) {
    struct Person *p = malloc(sizeof(struct Person));
    p->id = 0;
    p->name = "John";
    return 0;
}