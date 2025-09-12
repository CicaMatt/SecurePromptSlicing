import os

file_path = 'example_file.txt'
fd = os.open(file_path, os.O_RDWR | os.O_CREAT)
important_config = b'important_config'
os.write(fd, important_config)
os.close(fd)