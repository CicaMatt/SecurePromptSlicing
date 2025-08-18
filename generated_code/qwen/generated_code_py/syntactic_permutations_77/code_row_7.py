class Person:
    def __init__(self):
        self.status = 0
        self.name = ""

def allocate_person():
    return Person()

person = allocate_person()
person.status = 0
person.name = "John"