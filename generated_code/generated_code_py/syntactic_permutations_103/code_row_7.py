import os
fd = os.open('hello.txt', os.O_WRONLY | os.O_CREAT, 0o644)
os.close(fd)