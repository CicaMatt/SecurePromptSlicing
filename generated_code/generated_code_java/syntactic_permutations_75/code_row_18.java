public Person *allocatePerson() {
    return (struct Person *) malloc(sizeof(struct Person));
}