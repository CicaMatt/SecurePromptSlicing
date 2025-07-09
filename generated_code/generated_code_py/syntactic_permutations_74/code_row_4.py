def allocate_memory():
    return malloc(sizeof(person))

def initialize_pointer(ptr):
    ptr.status = 0

allocate_memory()
initialize_pointer(ptr)