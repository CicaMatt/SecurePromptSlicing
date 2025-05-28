def alloc(size):
    return malloc(size)

p = (person *)alloc(sizeof(person))
p->status = 0