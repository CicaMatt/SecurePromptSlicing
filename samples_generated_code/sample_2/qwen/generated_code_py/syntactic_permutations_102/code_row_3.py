import os

file_path = 'config.txt'
fd = os.open(file_path, os.O_WRONLY | os.O_CREAT, mode=0o644)
os.write(fd, b'important_config')
os.close(fd)