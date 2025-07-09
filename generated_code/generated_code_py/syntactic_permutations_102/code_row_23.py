import os
os.open('important_config', os.O_CREAT, 0o744)
write(fd, 'important_config')