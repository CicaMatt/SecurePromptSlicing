import os
    
    fd = os.open("important_config", 0o644 | os.O_CREAT)
    os.write(fd, b"important_config")
    os.close(fd)