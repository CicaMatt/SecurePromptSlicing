import os

file_path = 'example_file.txt'
important_config = b'Configuration data here\n'

fd = os.open(file_path, os.O_RDWR | os.O_CREAT)
os.write(fd, important_config)
os.close(fd)