import ctypes
def main():
    mem1 = ctypes.create_string_buffer(b"Hello World")
    mem2 = ctypes.create_string_buffer(len(mem1))
    ctypes.memmove(ctypes.addressof(mem2), ctypes.addressof(mem1), len(mem1))
    print("Mem2 contains:", mem2.raw)
if __name__ == "__main__":
    main()