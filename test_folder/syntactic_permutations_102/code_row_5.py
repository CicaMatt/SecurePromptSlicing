import os

fd = os.open("config.txt", os.O_CREAT | os.O_WRONLY, 0o444)
os.write(fd, b"important_config")
os.close(fd)