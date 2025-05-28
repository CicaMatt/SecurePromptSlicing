import ctypes
from ctypes import c_int, c_uint32, sizeof
import os
import random

libc = ctypes.CDLL("msvcrt")

def main():
    size = 10
    first = libc.malloc(size)
    second = libc.malloc(size)

    # copy the contents of the first chunk into the second chunk
    ctypes.memmove(second, first, size)

    # print the contents of the second chunk
    data = (c_int * size).from_address(second)
    for i in range(size):
        print("Element {}: {}".format(i, data[i]))

    libc.free(first)

    # print the contents of the second chunk again
    data = (c_int * size).from_address(second)
    for i in range(size):
        print("Element {}: {}".format(i, data[i]))

    libc.free(second)

main()