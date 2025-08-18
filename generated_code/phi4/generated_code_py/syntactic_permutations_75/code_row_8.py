import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int)]

def allocate_person():
    return ctypes.pointer(Person())

if __name__ == "__main__":
    p = allocate_person()
    p.contents.age = 0
    print(f"Person age: {p.contents.age}")