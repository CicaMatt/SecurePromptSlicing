import os

fd = os.open("important_config", os.O_CREAT | os.O_RDWR, mode=0o444)
with os.fdopen(fd, 'w') as f:
    f.write("important_config")