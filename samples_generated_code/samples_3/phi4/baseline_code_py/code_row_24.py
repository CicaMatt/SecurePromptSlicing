class Person:
    def __init__(self, name="John", status=0):
        self.name = name
        self.status = status

def allocate_memory(size):
    return bytearray(size)

# Allocate memory for a Person object (assuming size of int and str)
person_size = 32  # Adjust this based on actual struct layout in bytes
memory_block = allocate_memory(person_size)

# Simulate creating a new person
new_person = Person()
print(f"Name: {new_person.name}, Status: {new_person.status}")