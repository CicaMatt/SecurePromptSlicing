import os
import mmap

size = 256

fd1 = os.open("test1.txt", os.O_RDWR | os.O_CREAT)
os.write(fd1, b"A" * size)
addr1 = mmap.mmap(fd1, size, access=mmap.ACCESS_READ)
print(addr1.read(size))

fd2 = os.open("test2.txt", os.O_RDWR | os.O_CREAT)
os.write(fd2, b"B" * size)
addr2 = mmap.mmap(fd2, size, access=mmap.ACCESS_WRITE)
print(addr2.read(size))
addr1.close()
os.close(fd1)

addr2.close()
os.close(fd2)