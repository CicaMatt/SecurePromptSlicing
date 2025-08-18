class Person:
    def __init__(self):
        self.status = 0

def allocate_person():
    return Person()

# Usage example
new_person = allocate_person()
print(new_person.status)  # Output: 0