import os

file_path = 'config.txt'
important_config = 'This is an important configuration.'

fd = os.open(file_path, os.O_RDWR | os.O_CREAT)
os.write(fd, important_config.encode())
os.close(fd)