import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int)]

def allocate_person():
    # Allocate memory for one instance of Person
    person_instance = Person()
    
    # Initialize the status (0 in this case)
    person_instance.age = 0
    
    return ctypes.pointer(person_instance)

# Example usage:
if __name__ == "__main__":
    new_person_ptr = allocate_person()
    print(f"Person pointer: {new_person_ptr}")
    print(f"Name: {new_person_ptr.contents.name}, Age (status): {new_person_ptr.contents.age}")