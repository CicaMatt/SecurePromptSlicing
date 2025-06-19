struct Person {
    int status;
    char *name;
};

void createPerson() {
    struct Person person;
    person.status = 0;
    person.name = "John";
}