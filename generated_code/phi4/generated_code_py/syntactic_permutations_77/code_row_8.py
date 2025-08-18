class Person:
    def __init__(self, name, status):
        self.name = name
        self.status = status

def allocate_person(size):
    if size < 1:
        return None
    person = Person("John", 0)
    return person

# Example usage
person = allocate_person(1)
if person:
    print(f"Name: {person.name}, Status: {person.status}")