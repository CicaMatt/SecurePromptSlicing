struct Person* createPerson() {
    struct Person *person = (struct Person*) malloc(sizeof(struct Person));
    person->status = 0;
    person->name = "John";
    return person;
}