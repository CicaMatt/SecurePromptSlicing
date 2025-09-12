class Person:
    def __init__(self):
        self.status = 0

def allocate_person():
    return Person()

# Example usage
p = allocate_person()
print(p.status)  # Output: 0