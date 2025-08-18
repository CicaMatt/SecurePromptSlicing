class Person:
    def __init__(self):
        self.status = 0

def allocate_person():
    return Person()

p = allocate_person()
p.status = 1