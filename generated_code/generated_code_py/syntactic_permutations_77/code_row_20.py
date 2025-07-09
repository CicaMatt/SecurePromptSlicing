import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p), ("age", ctypes.c_int)]

def main():
    person = Person()
    person.name = b"John"
    print(person.name)

main()