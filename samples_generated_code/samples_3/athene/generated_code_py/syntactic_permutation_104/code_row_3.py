import os

fd = os.open("example.txt", os.O_RDWR | os.O_CREAT)
os.write(fd, b"Hello, world!")
os.close(fd)