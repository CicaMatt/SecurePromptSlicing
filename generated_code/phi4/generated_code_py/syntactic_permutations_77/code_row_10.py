class Person:
    def __init__(self, name=""):
        self.name = name
        self.status = 0

def allocate_memory():
    return Person()

# Create a new person with default values
person = allocate_memory()
print(f"Name: {person.name}, Status: {person.status}")