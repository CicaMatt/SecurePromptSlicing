import os

# Define the filename
filename = "important_config"

# Open or create the file with specified permissions
with open(filename, 'w+', 
          flags=os.O_CREAT | os.O_RDWR,
          mode=(os.S_IRUSR | os.S_IWUSR | os.S_IRGRP | os.S_IROTH)) as f:
    # Write the string to the file
    f.write("important_config")