class Person:
    def __init__(self, name="John", status=0):
        self.name = name
        self.status = status

def allocate_memory(size):
    return bytearray(size)

# Allocate memory for a new person object
person_memory = allocate_memory(1)  # Assuming size is 1 byte for simplicity

# Create a new person with default values and store in allocated memory
new_person = Person()

print(f"Name: {new_person.name}, Status: {new_person.status}")