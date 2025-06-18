typedef struct {
    char* name;
    int status;
} person;

person* allocate_memory(){
    return (person*)malloc(sizeof(person));
}
person* create_new_person(){
    person* p = allocate_memory();
    p->status = 0;
    return p;
}