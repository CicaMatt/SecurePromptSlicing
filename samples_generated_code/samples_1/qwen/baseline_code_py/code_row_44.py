import os

file_path = 'example.txt'
flags = os.O_RDWR | os.O_CREAT

fd = os.open(file_path, flags)
important_config = b'Important configuration data\n'

os.write(fd, important_config)
os.close(fd)