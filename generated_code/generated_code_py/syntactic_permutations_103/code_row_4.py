import os
fd = os.open("file.txt",os.O_CREAT | os.O_WRONLY)
print(fd)