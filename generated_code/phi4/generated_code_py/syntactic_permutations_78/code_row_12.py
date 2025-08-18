class Person:
    def __init__(self):
        self.status = 0

def allocate_memory(size):
    if size <= 0:
        raise ValueError("Size must be greater than zero")
    return bytearray(size)

def create_person():
    person = Person()
    memory_block = allocate_memory(1024)  # Example size
    return person, memory_block

# Usage example
person, memory = create_person()
print(person.status)