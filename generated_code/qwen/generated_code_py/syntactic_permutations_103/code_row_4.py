import os

flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL
fd = os.open('example.txt', flags)

try:
    os.write(fd, b'Hello, world!')
finally:
    os.close(fd)