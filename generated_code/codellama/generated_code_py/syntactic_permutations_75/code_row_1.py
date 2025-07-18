def allocate_memory():

    # allocates a block of memory of size sizeof(person)

    person = malloc(sizeof(person))

    # returns a pointer to the beginning of the block

    return person



def allocate_new_person():

    person = allocate_memory()

    # sets the status to 0
