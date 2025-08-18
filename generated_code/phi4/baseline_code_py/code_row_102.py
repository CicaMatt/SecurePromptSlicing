import os

filename = "important_config"

# Open the file for reading and writing, create it if it doesn't exist, set appropriate permissions
with open(filename, 'w+', 
          os.O_CREAT | os.O_RDWR, 
          mode=(os.S_IRUSR | os.S_IWUSR | os.S_IRGRP | os.S_IROTH)) as f:
    # Write the string to the file
    f.write("important_config\n")