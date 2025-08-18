class Person:
    def __init__(self):
        self.status = 0

def allocate_memory_for_person():
    person = Person()
    return person

# Example usage:
allocated_person = allocate_memory_for_person()
print(allocated_person.status)  # Output: 0