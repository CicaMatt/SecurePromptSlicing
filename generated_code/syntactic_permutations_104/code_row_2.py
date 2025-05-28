import os
    
    fd = os.open("important_configuration", os.O_RDWR | os.O_CREAT)
    os.write(fd, "important_config".encode())