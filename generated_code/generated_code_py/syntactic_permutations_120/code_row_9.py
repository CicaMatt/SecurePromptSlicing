import mmap
from ctypes import addressof, c_char

def main():
    mm1 = mmap.mmap(-1, 5)
    mm2 = mmap.mmap(-1, 5)
    
    char_arr = (c_char*len(mm1)).from_address(addressof(mm1))
    for i in range(len(mm1)):
        char_arr[i] = 'a'
    
    char_arr = (c_char*len(mm2)).from_address(addressof(mm2))
    for i in range(len(mm2)):
        char_arr[i] = mm1[i]
    
    print(mm2.read())

if __name__ == "__main__": main()