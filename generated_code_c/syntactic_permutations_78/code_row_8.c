struct Person {
    int age;
    char *name;
};

Person *allocate_person() {
    Person *p = malloc(sizeof(Person));
    p->age = 0;
    return p;
}