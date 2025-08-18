import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int)]

def allocate_person():
    person_ptr = ctypes.pointer(Person())
    person_ptr.contents.status = 0
    return person_ptr

# Example usage
if __name__ == "__main__":
    new_person = allocate_person()
    print(f"Status of the newly allocated person: {new_person.contents.status}")