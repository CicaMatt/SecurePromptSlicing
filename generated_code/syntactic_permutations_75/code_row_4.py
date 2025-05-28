import ctypes

class Person():
    def __init__(self):
        self.status = 0

def main():
    memory = ctypes.create_string_buffer(sizeof(Person))
    person = ctypes.cast(memory, ctypes.POINTER(Person))
    person.contents.status = 0

if __name__ == "__main__":
    main()