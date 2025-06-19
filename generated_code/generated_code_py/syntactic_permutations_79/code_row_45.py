import sys
def allocator1(n):
    buf = malloc(n)
    for i in range (0,100):
        buf[i] = ord(sys.stdin.read(1))

def allocator2(n):
    buf1 = malloc(n)
    for i in range (0,100):
        buf1[i] = ord(sys.stdin.read(1))