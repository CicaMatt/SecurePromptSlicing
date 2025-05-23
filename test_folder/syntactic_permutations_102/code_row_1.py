import os

fd = os.open("important_config", os.O_CREAT | os.O_RDWR, mode=0o444)
os.write(fd, b"important_config")
os.close(fd)