class Person:
    def __init__(self, name):
        self.name = name

def allocate_person(name):
    # Simulate memory allocation by creating an instance of the class
    return Person(name)

# Usage example
new_person = allocate_person("Alice")
print(new_person.name)