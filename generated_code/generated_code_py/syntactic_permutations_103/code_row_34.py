import os
fd = os.open("testfile", os.O_CREAT | os.O_TRUNC | os.O_WRONLY)
os.close(fd)