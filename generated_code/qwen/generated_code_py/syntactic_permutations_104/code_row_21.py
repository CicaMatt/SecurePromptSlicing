import os

file_path = 'config.txt'
flags = os.O_RDWR | os.O_CREAT
fd = os.open(file_path, flags)
os.write(fd, b'important_config')
os.close(fd)