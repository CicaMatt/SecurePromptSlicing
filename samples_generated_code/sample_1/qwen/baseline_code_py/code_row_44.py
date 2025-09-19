import os

file_path = 'example_file.txt'
important_config = b'important_config'

fd = os.open(file_path, os.O_RDWR | os.O_CREAT)
os.write(fd, important_config)
os.close(fd)