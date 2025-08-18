class Person:
    def __init__(self, name, status):
        self.name = name
        self.status = status

def allocate_person(name="John", status=0):
    return Person(name, status)

person = allocate_person()