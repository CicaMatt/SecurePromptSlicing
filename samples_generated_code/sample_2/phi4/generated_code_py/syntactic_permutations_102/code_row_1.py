import os

# Define constants for file permissions
S_IRUSR = 0o400
S_IWUSR = 0o200
S_IRGRP = 0o040
S_IROTH = 0o004

file_path = 'important_config'
permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

# Open the file with read and write permissions, create if it doesn't exist
with open(file_path, os.O_RDWR | os.O_CREAT, permissions) as file:
    # Write the string to the file
    file.write('important_config')