def allocate_person(size):
    return malloc(size)

def create_person():
    p = Person()
    p.status = 0
    return p