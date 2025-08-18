class Person:
    def __init__(self, size):
        self.status = 0
        self.name = ""
        # Simulating memory allocation with an array of bytes (size specified)
        self.memory_block = bytearray(size)

def create_person(size):
    person = Person(size)
    return person

# Example usage:
person1 = create_person(100)  # Allocate a block of memory of size 100
print(person1.status)         # Output: 0
print(person1.name)           # Output: ""


This code defines a `Person` class with attributes for `status`, `name`, and a simulated memory allocation using a `bytearray`. The `create_person` function initializes a new `Person` object.