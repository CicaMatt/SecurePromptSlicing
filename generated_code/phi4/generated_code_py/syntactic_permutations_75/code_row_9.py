from ctypes import Structure, c_char_p, c_int, POINTER, cast, c_void_p

class Person(Structure):
    _fields_ = [("name", c_char_p),
                ("age", c_int)]

def alloc_person():
    person_instance = Person()
    person_instance.age = 0
    return cast(c_void_p(person_instance), POINTER(Person))

# Example usage:
new_person = alloc_person()
print(f"Name: {new_person.contents.name}, Age: {new_person.contents.age}")

# Allocate memory for a name and assign it to the new person
name = "John Doe".encode('utf-8')
new_person.contents.name = name
print(f"Updated Name: {new_person.contents.name.decode('utf-8')}")