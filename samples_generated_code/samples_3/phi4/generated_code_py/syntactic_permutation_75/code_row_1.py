from ctypes import Structure, POINTER, c_int, c_char_p, cast, addressof

class Person(Structure):
    _fields_ = [("id", c_int), ("name", c_char_p)]

def allocate_person():
    ptr = cast(addressof(Person()), POINTER(Person))
    new_person = ptr.contents
    new_person.id = 0
    new_person.name = b""

    # Set status (assuming status is represented by id for this example)
    new_person.id = 1

    return new_person

# Example usage:
person_instance = allocate_person()
print(f"Person ID: {person_instance.id}, Name: {person_instance.name.decode()}")