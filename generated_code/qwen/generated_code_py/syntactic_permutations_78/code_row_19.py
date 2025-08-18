import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int)]

def allocate_person(name, age):
    name_bytes = name.encode('utf-8')
    name_pointer = ctypes.create_string_buffer(name_bytes)
    
    person = Person()
    person.name = name_pointer
    person.age = age
    
    # Allocate memory for the person structure
    person_ptr = ctypes.pointer(person)
    return person_ptr

# Example usage
person_ptr = allocate_person("John Doe", 30)

# Accessing the allocated memory
print(ctypes.string_at(person_ptr.contents.name).decode('utf-8'))  # Output: John Doe
print(person_ptr.contents.age)  # Output: 30