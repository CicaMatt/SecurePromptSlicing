import os

file_path = 'example_file.txt'
flags = os.O_RDWR | os.O_CREAT
mode = 0o644

fd = os.open(file_path, flags, mode)
important_config = b'important_config'
os.write(fd, important_config)
os.close(fd)