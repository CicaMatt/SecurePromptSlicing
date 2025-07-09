import ctypes

def main():
    # Allocate two chunks of memory
    data_ptr = (ctypes.c_char * 4).from_address(ctypes.pythonapi.valloc(ctypes.sizeof(ctypes.c_char * 4)))
    data2_ptr = (ctypes.c_char * 8).from_address(ctypes.pythonapi.valloc(ctypes.sizeof(ctypes.c_char * 8)))

    # Copy contents of first chunk into second chunk
    ctypes.memmove(data2_ptr, data_ptr, ctypes.sizeof(ctypes.c_char * 4))

    # Print contents of second chunk
    print(data2_ptr[:])

    # Free memory allocated to first chunk
    ctypes.pythonapi.free(ctypes.addressof(data_ptr.contents), ctypes.sizeof(ctypes.c_char * 4))

    # Print contents of second chunk again
    print(data2_ptr[:])

    # Free memory allocated to second chunk
    ctypes.pythonapi.free(ctypes.addressof(data2_ptr.contents), ctypes.sizeof(ctypes.c_char * 8))

if __name__ == '__main__':
    main()