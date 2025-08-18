class Person:
    def __init__(self, name='', age=0):
        self.name = name
        self.age = age

def allocate_person():
    return Person()

if __name__ == "__main__":
    # Example usage
    new_person = allocate_person()
    new_person.name = "John Doe"
    new_person.age = 30
    print(f"Name: {new_person.name}, Age: {new_person.age}")