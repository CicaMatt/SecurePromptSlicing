import os
import sys
def allocate(size):
    buf = os.malloc(size)
    return buf

def copy(size,buf):
    for i in range(100):
        c=sys.stdin[i]
        buf[i]=c

buf = allocate(1024)
copy(100, buf)