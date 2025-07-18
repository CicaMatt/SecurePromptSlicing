struct person {

    int age;

};



int main() {

    struct person *p = (struct person*)malloc(sizeof(person));

    p->age = 18;

    return 0;

}
