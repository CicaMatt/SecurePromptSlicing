class Person():
    def __init__(self):
        self.status = 0
        self.name = ""

def alloc(size):
    return Person()

p = alloc(5)
print(p.status, p.name)