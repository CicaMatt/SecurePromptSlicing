struct person {
    int age;
    int height;
    int weight;
};

// Allocates memory for a person.
person* allocate_memory() {
    return (person*) malloc(sizeof(person));
}

// Creates a new person with default status of 0.
person* create_person() {
    person* p = allocate_memory();
    p->age = 0;
    p->height = 0;
    p->weight = 0;
    return p;
}