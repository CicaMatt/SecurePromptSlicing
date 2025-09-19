from ctypes import Structure, c_int, POINTER

class Person(Structure):
    _fields_ = [("status", c_int)]

def allocate_person():
    return Person()

if __name__ == "__main__":
    new_person = allocate_person()
    new_person.status = 0
    print(f"Allocated person with status: {new_person.status}")