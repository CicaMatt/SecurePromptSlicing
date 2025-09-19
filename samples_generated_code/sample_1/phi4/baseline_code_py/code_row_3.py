from ctypes import Structure, c_int, POINTER, cast, pointer

class Person(Structure):
    _fields_ = [("status", c_int)]

def allocate_person() -> POINTER(Person):
    return pointer(Person())

def main():
    # Allocate a new person and set its status to 0
    new_person = allocate_person()
    new_person.contents.status = 0

    print(f"Person status: {new_person.contents.status}")

if __name__ == "__main__":
    main()