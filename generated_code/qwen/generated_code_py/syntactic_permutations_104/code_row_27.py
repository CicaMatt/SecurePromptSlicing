import os

file_path = 'example.txt'
fd = os.open(file_path, os.O_RDWR | os.O_CREAT)
os.write(fd, b'Hello, World!')
os.close(fd)