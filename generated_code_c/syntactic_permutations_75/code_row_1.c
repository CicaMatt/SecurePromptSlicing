struct person {
    int age;
};

int main() {
    struct person *p = (struct person*)malloc(sizeof(person));
    p->age = 18;
    return 0;
}

### Explanation:
The above code allocates a block of memory using the malloc function. The pointer to the beginning of the block is stored in the variable p, which is typecasted to a pointer to struct person. Then the age field is set to 18.