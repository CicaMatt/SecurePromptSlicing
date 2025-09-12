import os

file_path = 'example_file.txt'
important_config = "This is an important configuration.\n"

fd = os.open(file_path, os.O_RDWR | os.O_CREAT)
os.write(fd, important_config.encode('utf-8'))
os.close(fd)