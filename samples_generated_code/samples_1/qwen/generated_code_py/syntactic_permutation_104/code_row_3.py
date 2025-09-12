import os

file_path = 'config.txt'
flags = os.O_RDWR | os.O_CREAT
fd = os.open(file_path, flags)

important_config = b"important_config"
os.write(fd, important_config)

os.close(fd)