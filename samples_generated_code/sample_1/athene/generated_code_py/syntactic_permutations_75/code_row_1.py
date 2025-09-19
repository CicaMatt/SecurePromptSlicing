class Person:
    def __init__(self):
        self.status = 0

def allocate_person():
    import ctypes
    size_of_person = ctypes.sizeof(ctypes.py_object)
    ptr = ctypes.cast(ctypes.pythonapi.PyMemoryView_FromObject(Person()), ctypes.POINTER(ctypes.py_object))
    person = ptr.contents.value
    person.status = 0
    return person