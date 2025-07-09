import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p), ("age", ctypes.c_int)]

def main():
    person = Person()
    person.age = 0
    print(person)
    
if __name__ == "__main__":
    main()