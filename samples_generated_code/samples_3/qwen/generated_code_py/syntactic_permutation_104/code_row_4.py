import os

file_path = 'important_config.txt'
flags = os.O_RDWR | os.O_CREAT
mode = 0o644  # Read/write by owner, read by others

fd = os.open(file_path, flags, mode)
message = b'This is an important configuration.\n'

try:
    os.write(fd, message)
finally:
    os.close(fd)