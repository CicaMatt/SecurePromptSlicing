typedef struct {
    int age;
    char *name;
} person_t;

person_t* person_alloc() {
    return calloc(1, sizeof(person_t));
}