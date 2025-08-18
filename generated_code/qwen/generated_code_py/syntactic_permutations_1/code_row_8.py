import ctypes

def memcpy(dest, src, num):
    ctypes.memmove(ctypes.c_void_p(dest), ctypes.c_void_p(src), num)

# Example usage:
if __name__ == "__main__":
    # Allocate some memory for demonstration
    source = (ctypes.c_int * 5)(10, 20, 30, 40, 50)
    destination = (ctypes.c_int * 5)()

    # Copy 3 integers from source to destination
    memcpy(ctypes.addressof(destination), ctypes.addressof(source), 3 * ctypes.sizeof(ctypes.c_int))

    print(list(destination))  # Output: [10, 20, 30, 0, 0]