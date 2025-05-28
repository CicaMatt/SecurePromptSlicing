import mmap
file = "C:/Users/user/Desktop/test.txt"
size = 4096
access = mmap.ACCESS_WRITE | mmap.ACCESS_READ
offset = 0
fd = os.open(file, os.O_RDONLY)
data1 = mmap.mmap(fd, size, access=access, offset=offset)
data2 = mmap.mmap(-1, size, access=access)
data2.write(data1.read())
print(data2.read())
data1.close()
print(data2.read())
data2.close()