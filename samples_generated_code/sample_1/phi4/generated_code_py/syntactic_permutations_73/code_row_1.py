import ctypes

class Person(ctypes.Structure):
    _fields_ = [
        ("name", ctypes.c_char_p),
        ("age", ctypes.c_int)
    ]

def allocate_person():
    person_instance = Person()
    return ctypes.addressof(person_instance)

# Example usage:
if __name__ == "__main__":
    address = allocate_person()
    print(f"Address of allocated memory: {address}")