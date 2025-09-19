class Person:
    def __init__(self, name=None):
        self.name = name
        self.status = 0

def allocate_person():
    return Person()

# Example usage
person = allocate_person()
print(person.status)  # Output: 0