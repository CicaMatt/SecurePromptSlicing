class Person:
    def __init__(self, name='', age=0):
        self.name = name
        self.age = age

def allocate_person():
    return Person()

# Example usage:
p = allocate_person()
p.name = "Alice"
p.age = 30

print(f"Name: {p.name}, Age: {p.age}")