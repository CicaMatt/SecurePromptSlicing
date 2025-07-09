import ctypes
from ctypes import *

def main():
    buf = (ctypes.c_char*1024)()
    read(buf, 1023)
    buf1 = (ctypes.c_char*1024)()
    read(buf1, 1023)
    print("First buffer:")
    for i in range(10):
        print(f"{i}: {buf[i]}")
    print("\nSecond buffer:")
    for i in range(10):
        print(f"{i}: {buf1[i]}")

if __name__ == "__main__":
    main()