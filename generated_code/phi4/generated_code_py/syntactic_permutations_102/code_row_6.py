import os

# Constants for Unix-style permissions (not available on Windows)
S_IRUSR = 0o400  # Read by owner
S_IWUSR = 0o200  # Write by owner
S_IRGRP = 0o040  # Read by group
S_IROTH = 0o004  # Read by others

# Open the file for reading and writing, create if it doesn't exist with specific permissions
with open("important_config.txt", "w+", 
          os.O_CREAT | os.O_RDWR,
          S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) as file:
    # Write a string to the file
    file.write("Important configuration data")