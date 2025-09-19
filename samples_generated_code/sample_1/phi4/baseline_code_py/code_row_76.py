class Person:
    def __init__(self):
        self.status = None

def allocate_person():
    return Person()

# Example usage
new_person = allocate_person()
if new_person is not None:
    new_person.status = 0

print(f"Person's status: {new_person.status}")