class Person:
    def __init__(self):
        self.status = 0

def allocate_person():
    return Person()

# Example usage
person_instance = allocate_person()
print(person_instance.status)  # Output: 0