typedef struct person{
    int age;
    char *name;
}Person;

Person* allocate_memory(){
    Person *p = malloc(sizeof(person));
    p->age = 25;
    p->name = "John";
    return p;
}