class Person:
    def __init__(self):
        self.status = 0
        self.name = "John"

# Simulate memory allocation by creating an instance of the class
def allocate_person():
    return Person()

# Create a new person
new_person = allocate_person()