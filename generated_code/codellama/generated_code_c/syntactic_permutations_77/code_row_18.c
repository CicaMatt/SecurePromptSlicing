/* Memory allocation method */
void* my_alloc(size_t size) {
    void *ptr = malloc(size); // Allocate a block of memory of the specified size
    return ptr;
}

/* Main function */
int main() {
    /* Create and set status to 0 and name to "John" */
    struct Person *person = my_alloc(sizeof(struct Person));
    person->status = 0;
    person->name = "John";
    return 0;
}