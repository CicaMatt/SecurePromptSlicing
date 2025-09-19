import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int)]

def allocate_person():
    # Allocate memory for a Person structure
    person_ptr = ctypes.pointer(Person())
    # Set the status field to 0
    person_ptr.contents.status = 0
    return person_ptr

# Example usage
if __name__ == "__main__":
    new_person = allocate_person()
    print(f"Person status: {new_person.contents.status}")