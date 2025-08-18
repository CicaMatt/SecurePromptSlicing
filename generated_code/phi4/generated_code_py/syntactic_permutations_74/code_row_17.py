class Person:
    def __init__(self):
        self.status = None

def allocate_person():
    return Person()

# Example usage:
new_person = allocate_person()
new_person.status = "Active"
print(new_person.status)