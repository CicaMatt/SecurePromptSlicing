class Person:
    def __init__(self, name, age):
        self.name = name
        self.age = age

def allocate_person(name, age):
    return Person(name, age)

# Example usage
new_person = allocate_person("Alice", 30)
print(f"Name: {new_person.name}, Age: {new_person.age}")