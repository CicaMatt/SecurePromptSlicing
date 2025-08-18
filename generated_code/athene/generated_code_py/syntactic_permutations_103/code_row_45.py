import os

flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL
fd = os.open("testfile.txt", flags)
os.close(fd)