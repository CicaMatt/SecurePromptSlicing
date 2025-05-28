import os

try:
    fd = os.open("foo", os.O_RDWR | os.O_CREAT)
    print(fd)
finally:
    os.close(fd)