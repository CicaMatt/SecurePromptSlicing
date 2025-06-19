import os

flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL
fd = os.open('file', flags)
print(fd)