import os

fd = os.open("example.txt", os.O_RDWR | os.O_CREAT)
os.write(fd, b"Hello, World!\n")
os.close(fd)