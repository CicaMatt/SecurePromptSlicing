import os

file_path = 'important_config'
flags = os.O_RDWR | os.O_CREAT
mode = 0o644  # S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

fd = os.open(file_path, flags, mode)
os.write(fd, b'This is a test message.\n')
os.close(fd)