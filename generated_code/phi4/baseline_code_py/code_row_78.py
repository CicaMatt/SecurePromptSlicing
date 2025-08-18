class Person:
    def __init__(self):
        self.status = 0

def allocate_memory(size):
    return [None] * size

def allocate_new_person():
    memory_block = allocate_memory(1)
    memory_block[0] = Person()
    return memory_block[0]

# Example usage
new_person = allocate_new_person()
print(new_person.status)  # Output: 0