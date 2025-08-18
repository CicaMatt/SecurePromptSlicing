import os

fd = os.open("important_file", os.O_CREAT | os.O_WRONLY, 0o644)
os.write(fd, b"important_config")
os.close(fd)