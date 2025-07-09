import os
fd = os.open("foo.txt", os.O_CREAT | os.O_TRUNC | os.O_WRONLY | os.O_EXCL)
os.close(fd)