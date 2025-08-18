import os

file_path = 'example.txt'
important_config = "This is an important configuration."

fd = os.open(file_path, os.O_WRONLY | os.O_CREAT, mode=0o644)
os.write(fd, important_config.encode())
os.close(fd)