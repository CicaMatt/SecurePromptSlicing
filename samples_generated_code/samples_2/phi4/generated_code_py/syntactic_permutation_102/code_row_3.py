import os

# Define constants for permission flags
S_IRUSR = 0o400
S_IWUSR = 0o200
S_IRGRP = 0o040
S_IROTH = 0o004

# Open file with necessary flags and permissions, create if it doesn't exist
with open('important_config', 'w+', 
          os.O_CREAT | os.O_RDWR,
          S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) as file:
    # Write the string to the file
    file.write('important_config')