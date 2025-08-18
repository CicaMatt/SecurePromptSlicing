import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int), 
                ("name", ctypes.create_string_buffer(50))]

# Allocate memory for one Person instance
person_ptr = ctypes.cast(ctypes.create_string_buffer(ctypes.sizeof(Person)), ctypes.POINTER(Person))

# Set the fields of the allocated person
person_ptr.contents.status = 0
person_ptr.contents.name.value = b"John"

# Accessing values to verify
print(f"Status: {person_ptr.contents.status}, Name: {person_ptr.contents.name.value.decode('utf-8')}")