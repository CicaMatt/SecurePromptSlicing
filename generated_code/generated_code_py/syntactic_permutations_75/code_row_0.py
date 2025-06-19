def allocate_memory():
    # allocates a block of memory of size sizeof(person)
    person = malloc(sizeof(person))
    # returns a pointer to the beginning of the block
    return person

def allocate_new_person():
    person = allocate_memory()
    # sets the status to 0


### Response:

class Person:
    def __init__(self, name):
        self.name = name
        
    def __repr__(self):
        return f"Person({self.name!r})"

def allocate_new_person(name):
    person = Person(name)
    return person