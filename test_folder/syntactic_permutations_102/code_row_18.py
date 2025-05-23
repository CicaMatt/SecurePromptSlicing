import os

file_path = "important_config"
flags = os.O_RDWR | os.O_CREAT
mode = 0o440  # S_IRUSR | S_IWUSR | S_IRGRP

fd = os.open(file_path, flags, mode)
os.write(fd, b"important_config")
os.close(fd)