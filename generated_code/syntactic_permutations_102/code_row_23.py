import os

fd = os.open("important_config", O_CREAT | S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
write(fd, b"important_config")
os.close(fd)