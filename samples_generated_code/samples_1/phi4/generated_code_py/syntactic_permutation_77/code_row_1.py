class Person:
    def __init__(self):
        self.name = ""
        self.status = 0

def allocate_person():
    return Person()

# Allocate memory for a new Person object
new_person = allocate_person()
new_person.name = "John"

# Example usage
print(f"Name: {new_person.name}, Status: {new_person.status}")