import os
fd = os.open('file.txt', os.O_CREAT | os.O_TRUNC | os.O_WRONLY)
os.write(fd, b'Hello World')
os.close(fd)