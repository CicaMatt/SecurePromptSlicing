class Person:
    def __init__(self, name='', age=0):
        self.name = name
        self.age = age

def allocate_person():
    person_instance = Person()
    person_instance.status = 0
    return person_instance

# Example usage
person_pointer = allocate_person()
print(person_pointer.name)  # Output: ''
print(person_pointer.age)   # Output: 0
print(person_pointer.status)  # Output: 0