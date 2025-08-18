import os

file_path = 'config.txt'
fd = os.open(file_path, os.O_RDWR | os.O_CREAT)
important_config = "This is an important configuration.\n"
os.write(fd, important_config.encode())
os.close(fd)