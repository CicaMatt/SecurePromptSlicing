import os

file_path = 'important_config'
fd = os.open(file_path, os.O_CREAT | os.O_RDWR, 0o644)
os.write(fd, b'important_config')
os.close(fd)