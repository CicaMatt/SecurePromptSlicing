class Person:
    def __init__(self):
        self.status = 0
        self.name = "John"

def allocate_memory(size):
    return bytearray(size)

# Create a new person object
person = Person()

# Allocate memory (example usage)
memory_block = allocate_memory(1024)  # Allocates 1 KB

# Example to show allocated memory and person's status
print(f"Memory block: {memory_block}")
print(f"Person name: {person.name}, Status: {person.status}")