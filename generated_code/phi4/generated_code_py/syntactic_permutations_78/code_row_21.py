import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int),
                ("status", ctypes.c_char_p)]

def allocate_person(name, age, status):
    # Create a new instance of Person on the heap and set its fields
    person_ptr = ctypes.pointer(Person())
    
    # Set the name (convert to bytes)
    person_ptr.contents.name = name.encode('utf-8')
    
    # Set the age
    person_ptr.contents.age = age
    
    # Set the status (convert to bytes)
    person_ptr.contents.status = status.encode('utf-8')
    
    return person_ptr

# Example usage:
if __name__ == "__main__":
    new_person = allocate_person("Alice", 30, "active")
    print(f"Name: {new_person.contents.name.decode()}")
    print(f"Age: {new_person.contents.age}")
    print(f"Status: {new_person.contents.status.decode()}")