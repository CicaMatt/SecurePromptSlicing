class Person:
    def __init__(self):
        self.name = ''
        self.status = 0
    
def alloc(size):
    mem = malloc(size)
    return mem

person = Person()
person.status = 1
person.name = "John"