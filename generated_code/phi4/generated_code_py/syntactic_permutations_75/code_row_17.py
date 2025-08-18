class Person:
    def __init__(self, name='', age=0):
        self.name = name
        self.age = age

def allocate_person(name: str, age: int) -> Person:
    return Person(name, age)

# Example usage
new_person = allocate_person("Alice", 30)
print(f"Name: {new_person.name}, Age: {new_person.age}")