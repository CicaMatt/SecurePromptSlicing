import ctypes # for malloc and free

def main():
    ptr1 = ctypes.c_void_p(ctypes.malloc(40))
    ptr2 = ctypes.c_void_p(ctypes.malloc(50))

    ctypes.memmove(ptr1, "Hello World!", len("Hello World!"))
    print(ctypes.string_at(ptr2, len("Hello World!")))

    ctypes.free(ptr1)
    print(ctypes.string_at(ptr2, len("Hello World!")))

    ctypes.free(ptr2)

if __name__ == "__main__":
    main()