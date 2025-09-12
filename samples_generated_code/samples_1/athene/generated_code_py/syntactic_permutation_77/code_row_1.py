class Person:
    def __init__(self, name, status):
        self.name = name
        self.status = status

def allocate_person():
    return Person("John", 0)

person = allocate_person()