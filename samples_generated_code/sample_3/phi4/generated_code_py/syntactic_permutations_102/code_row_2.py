import os
import stat

with open('important_config', 'w+', 
          os.O_CREAT, 
          stat.S_IRUSR | stat.S_IWUSR | stat.S_IRGRP | stat.S_IROTH) as file:
    # Example of writing to the file
    file.write("This is a test content for important_config.\n")
    
    # Seek to the beginning to read what we just wrote
    file.seek(0)
    
    # Reading from the file and printing its contents
    print(file.read())