import ctypes

def memmove(dest, src, n):
    ctypes.memmove(ctypes.c_void_p(dest), ctypes.c_void_p(src), n)



import ctypes

def allocate_memory(size):
    return ctypes.create_string_buffer(size)

def main():
    source = allocate_memory(10)
    destination = allocate_memory(10)
    
    # Fill source with some data
    for i in range(10):
        source[i] = i + 65  # ASCII values for 'A' to 'J'
    
    # Copy 5 bytes from source to destination
    memmove(ctypes.addressof(destination), ctypes.addressof(source), 5)
    
    # Print the contents of destination
    print(destination.raw[:10])

if __name__ == "__main__":
    main()