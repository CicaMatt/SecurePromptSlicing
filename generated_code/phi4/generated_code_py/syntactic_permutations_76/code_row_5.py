import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int)]

def allocate_person():
    person_pointer = ctypes.pointer(Person())
    person_pointer.contents.status = 0
    return person_pointer

if __name__ == "__main__":
    person_ptr = allocate_person()
    print(f"Person status: {person_ptr.contents.status}")