import os

def write_config():
    fd = os.open("important_config", os.O_CREAT | os.O_WRONLY, mode=0o444)
    os.write(fd, b"important_config")
    os.close(fd)

write_config()