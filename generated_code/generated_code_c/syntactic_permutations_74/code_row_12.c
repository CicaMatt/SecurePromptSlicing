typedef struct person {
        int age;
        char *name;
    };

    person* allocate() {
        return (person*)malloc(sizeof(person));
    }