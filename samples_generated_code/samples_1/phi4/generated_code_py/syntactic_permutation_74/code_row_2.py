class Person:
    def __init__(self, name='', age=0):
        self.name = name
        self.age = age
        self.status = 0

def allocate_person(name='', age=0):
    return Person(name, age)

# Example usage
new_person = allocate_person("John Doe", 30)
print(new_person.name, new_person.age, new_person.status)