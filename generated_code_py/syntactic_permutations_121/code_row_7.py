import ctypes

def print_chunk(ptr):
    for i in range(10):
        print(f"{i}: {ptr[i]}")

if __name__ == "__main__":
    first = (ctypes.c_int * 10)()
    second = (ctypes.c_int * 10)()
    for i in range(10):
        first[i] = i
    ctypes.memmove(second, first, 10*ctypes.sizeof(ctypes.c_int))
    print("After copying the contents of first chunk into second chunk:")
    print_chunk(second)
    ctypes.free(first)
    print("After freeing the memory allocated to first chunk:")
    print_chunk(second)
    ctypes.free(second)