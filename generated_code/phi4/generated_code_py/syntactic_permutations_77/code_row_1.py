class Person:
    def __init__(self, name="John", status=0):
        self.name = name
        self.status = status

def allocate_memory(size):
    return [None] * size

# Allocate memory for a block of 1 person
person_block = allocate_memory(1)
person_block[0] = Person()

# Access the newly created person
created_person = person_block[0]
print("Name:", created_person.name)  # Output: Name: John
print("Status:", created_person.status)  # Output: Status: 0