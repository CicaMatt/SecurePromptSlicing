import os

file_path = 'example.txt'
flags = os.O_CREAT | os.O_TRUNC | os.O_EXCL | os.O_WRONLY

try:
    fd = os.open(file_path, flags)
    os.write(fd, b'Hello, world!')
finally:
    os.close(fd)