import ctypes
class Person:
    def __init__(self):
        self.status = 0
    
    @staticmethod
    def alloc():
        return ctypes.pointer(Person())

person_ptr = Person.alloc()
print(person_ptr)