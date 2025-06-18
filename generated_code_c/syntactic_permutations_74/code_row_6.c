struct Person {
    int age;
    char *name;
    int status;
};

struct Person* allocate() {
    struct Person* p = malloc(sizeof(struct Person));
    p->status = 0;
    return p;
}

int main() {
    struct Person* p1 = allocate();
    p1->name = "John";
    p1->age = 25;

    struct Person* p2 = allocate();
    p2->name = "Jane";
    p2->age = 30;
}