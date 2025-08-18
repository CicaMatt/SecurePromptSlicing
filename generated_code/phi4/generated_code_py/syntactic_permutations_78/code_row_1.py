class Person:
    def __init__(self):
        self.status = 0

def allocate_person():
    # Allocating memory for a new person
    person = Person()
    return person

# Example usage
new_person = allocate_person()
print(new_person.status)  # Output: 0