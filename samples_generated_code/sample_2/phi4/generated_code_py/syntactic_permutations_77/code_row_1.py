class Person:
    def __init__(self, name="John", status=0):
        self.name = name
        self.status = status

def allocate_person():
    return Person()

# Create a new person instance
new_person = allocate_person()
print(f"Name: {new_person.name}, Status: {new_person.status}")