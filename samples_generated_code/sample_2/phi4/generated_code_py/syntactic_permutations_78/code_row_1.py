class Person:
    def __init__(self, name):
        self.name = name
        self.status = 0

def allocate_person(name):
    return Person(name)

# Example usage
p = allocate_person("Alice")
print(p.name, p.status)