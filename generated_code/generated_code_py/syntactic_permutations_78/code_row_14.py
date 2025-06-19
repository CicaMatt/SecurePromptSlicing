def malloc(size):
    return 0

def new_person():
    p = malloc(sizeof(Person))
    p.status = 0
    return p