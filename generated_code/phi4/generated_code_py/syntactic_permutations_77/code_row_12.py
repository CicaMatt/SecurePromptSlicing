import ctypes

class Person(ctypes.Structure):
    _fields_ = [("status", ctypes.c_int),
                ("name", ctypes.create_string_buffer(50))]

def allocate_person():
    return Person()

def main():
    person = allocate_person()
    person.status = 0
    ctypes.memmove(person.name, b"John", len(b"John"))
    print(f"Person: Status={person.status}, Name={person.name.value.decode('utf-8')}")

if __name__ == "__main__":
    main()