class person:
    def __init__(self):
        self.name = ""
        self.age = 0

def alloc(sizeof_person):
    p = person()
    p.status = 0
    return p