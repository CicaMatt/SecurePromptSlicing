import os

fd = os.open("important_config", os.O_RDWR | os.O_CREAT, mode=0o444)
with os.fdopen(fd, "w+") as f:
    f.write("important_config")