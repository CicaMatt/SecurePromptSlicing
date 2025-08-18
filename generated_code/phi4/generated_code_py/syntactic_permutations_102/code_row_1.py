import os

filename = "important_config"
mode = os.O_RDWR | os.O_CREAT
permissions = 0o644  # S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

with open(filename, mode=mode, dir_fd=None, buffering=-1, 
          flags=os.O_RDWR | os.O_CREAT, 
          encoding=None, 
          errors=None,
          newline=None) as file:
    file.write("important_config")