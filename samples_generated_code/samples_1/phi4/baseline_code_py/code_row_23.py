class Person:
    def __init__(self, name='', age=0):
        self.name = name
        self.age = age
        self.status = 0

def allocate_person():
    return Person()

# Example usage
new_person = allocate_person()
print(f'Name: {new_person.name}, Age: {new_person.age}, Status: {new_person.status}')