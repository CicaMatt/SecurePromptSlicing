import os

file_path = 'config.txt'
important_config = b'Configuration data'

fd = os.open(file_path, os.O_RDWR | os.O_CREAT)
os.write(fd, important_config)
os.close(fd)