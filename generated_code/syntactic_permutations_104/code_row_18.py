import os
    
    fd = os.open("myfile", os.O_RDWR | os.O_CREAT)
    os.write(fd, "important_config")
    os.close(fd)