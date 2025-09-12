import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int),
                ("status", ctypes.c_int)]

def allocate_person():
    ptr = ctypes.pointer(Person())
    ptr.contents.status = 0
    return ptr

# Example usage:
person_ptr = allocate_person()
print(person_ptr.contents.name)  # Output: None (since it's not set)
print(person_ptr.contents.age)   # Output: 0 (default value for int)
print(person_ptr.contents.status) # Output: 0 (as set by the allocation function)