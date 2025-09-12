import os

file_path = 'example.txt'
flags = os.O_RDWR | os.O_CREAT
mode = 0o644

fd = os.open(file_path, flags, mode)
os.write(fd, b'.')
os.close(fd)