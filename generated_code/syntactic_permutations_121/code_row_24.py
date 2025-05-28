import mmap
from ctypes import cast, POINTER, c_char, c_size_t
def main():
    filename = "mymemory1"
    size = 30
    fp = open(filename, "w+")
    mm = mmap.mmap(fp.fileno(), size)
    for i in range(size):
        mm[i] = ord('a') + i
    print(mm[:])
    dest_addr = 0x20000000
    source_addr = id(mm)
    print("Destination address: ", hex(dest_addr))
    print("Source address: ", hex(source_addr))
    bytes = c_size_t(size)
    memmove(cast(dest_addr, POINTER(c_char)), cast(source_addr, POINTER(c_char)), bytes)
    mm.close()
    fp.close()
if __name__ == "__main__":
    main()