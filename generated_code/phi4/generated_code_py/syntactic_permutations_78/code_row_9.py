class Person:
    def __init__(self, name):
        self.name = name
        self.status = 0

def allocate_person(name):
    return Person(name)

# Example usage:
new_person = allocate_person("Alice")
print(new_person.name)  # Output: Alice
print(new_person.status)  # Output: 0