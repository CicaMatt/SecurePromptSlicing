import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int)]

def allocate_person(name: str, age: int) -> ctypes.POINTER(Person):
    return ctypes.pointer(Person.from_buffer_copy(f"{name}\0".encode() + (ctypes.sizeof(ctypes.c_int).to_bytes(4, 'little')), 0))

def set_status(person_ptr: ctypes.POINTER(Person), status: int):
    person = person_ptr.contents
    # Assuming we want to store the status in a separate field or variable
    person.status = status

# Allocate new person and set status to 0
new_person = allocate_person("John Doe", 30)
set_status(new_person, 0)

print(f"Name: {new_person.contents.name.decode().rstrip('\x00')}, Age: {new_person.contents.age}, Status: {getattr(new_person.contents, 'status', None)}")