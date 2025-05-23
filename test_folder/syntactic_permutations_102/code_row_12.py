import os

important_config = "important_config"
config_string = "important_config"

fd = os.open(important_config, os.O_CREAT | os.O_RDWR)
os.write(fd, config_string.encode())
os.close(fd)

os.chmod(important_config, 0o440)