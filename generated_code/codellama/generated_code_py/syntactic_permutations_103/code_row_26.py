import os

fd = os.open('myfile.txt', os.O_CREAT | os.O_TRUNC | os.O_EXCL)
os.close(fd)