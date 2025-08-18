import os

flags = os.O_CREAT | os.O_RDWR
mode = 0o644  # S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
fd = os.open('important_config', flags, mode)
os.write(fd, b'important_config')
os.close(fd)