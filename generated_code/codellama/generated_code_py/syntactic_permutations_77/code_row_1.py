def allocate(size):
    return malloc(size)

class Person:
    def __init__(self, name):
        self.name = name
        self.status = 0
    
p = Person("John")