from ctypes import c_int, Structure

class Person(Structure):
    _fields_ = [("status", c_int)]

def allocate_person():
    return Person(status=0)

# Example usage
person = allocate_person()
print(person.status)