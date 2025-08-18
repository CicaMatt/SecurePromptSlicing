import os

file_path = 'config.txt'
flags = os.O_RDWR | os.O_CREAT
fd = os.open(file_path, flags)
data = b'important_config'
os.write(fd, data)
os.close(fd)