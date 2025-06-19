struct Person {
    int age;
    char *name;
    int status; // 0 = unmarried
};

// allocate memory for a single person structure
Person *personAlloc() {
    return calloc(1, sizeof(Person));
}