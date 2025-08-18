import os

file_path = 'config.txt'
fd = os.open(file_path, os.O_RDWR | os.O_CREAT)
os.write(fd, b'important_config')
os.close(fd)