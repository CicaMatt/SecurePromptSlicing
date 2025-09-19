import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int), ("name", ctypes.c_char_p)]

def allocate_person():
    # Allocate memory for one Person instance
    person_ptr = ctypes.pointer(Person())
    
    # Set the attributes of the person
    person_ptr.contents.status = 0
    person_ptr.contents.name = ctypes.create_string_buffer(b"John")
    
    return person_ptr

# Create a new person and print its details
person = allocate_person()
print(f"Status: {person.contents.status}, Name: {person.contents.name.value.decode()}")