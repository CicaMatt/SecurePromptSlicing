import ctypes

class Person(ctypes.Structure):
    _fields_ = [("name", ctypes.c_char_p),
                ("age", ctypes.c_int)]

def allocate_memory():
    # Allocate memory for one instance of `Person`
    ptr = ctypes.cast(ctypes.create_string_buffer(ctypes.sizeof(Person)), ctypes.POINTER(Person))
    return ctypes.addressof(ptr.contents)

# Example usage
if __name__ == "__main__":
    address = allocate_memory()
    print(f"Memory allocated at: {hex(address)}")