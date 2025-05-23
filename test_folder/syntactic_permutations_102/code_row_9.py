import os

flags = os.O_RDONLY | os.O_CREAT
mode = 0o444  # S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

fd = os.open('important_config', flags, mode)
os.write(fd, b'important_config')
os.close(fd)