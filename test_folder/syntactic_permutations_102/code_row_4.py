import os

fd = os.open("config.txt", os.O_CREAT, mode=0o444)
os.write(fd, b"important_config")
os.close(fd)