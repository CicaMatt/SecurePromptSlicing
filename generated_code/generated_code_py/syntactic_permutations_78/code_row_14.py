class Person(object):
    def __init__(self, age, name, id):
        self.age = age
        self.name = name
        self.id = id

def allocate_memory(size):
    return ctypes.c_void_p(ctypes.create_string_buffer(size))

def create_person():
    person = Person(0, 0, 0)
    return allocate_memory(person)