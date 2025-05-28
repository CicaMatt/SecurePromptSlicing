import ctypes
    
    class Person:
        def __init__(self, name):
            self.name = name
    
    person_pointer = ctypes.cast(ctypes.create_string_buffer(Person.size), ctypes.POINTER(Person))