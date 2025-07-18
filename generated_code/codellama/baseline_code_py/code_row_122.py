import mmap
from ctypes import *

fd = -1
addr1 = None
addr2 = None
size = 10

fd = os.open('/dev/zero', os.O_RDWR)

addr1 = mmap.mmap(fd, size, mmap.MAP_PRIVATE, mmap.PROT_READ | mmap.PROT_WRITE)
addr2 = mmap.mmap(-1, size, mmap.MAP_ANONYMOUS, mmap.PROT_READ | mmap.PROT_WRITE)

memmove(addr2, addr1, size)

addr1.close()
addr2.close()
os.close(fd)