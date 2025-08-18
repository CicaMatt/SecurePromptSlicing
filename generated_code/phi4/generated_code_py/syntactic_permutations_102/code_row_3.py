import os

# Define the path to the file
file_path = 'important_config'

# Define the mode: read/write, create if not exists, set appropriate permissions
mode = os.O_RDWR | os.O_CREAT
permissions = (os.S_IRUSR | os.S_IWUSR | os.S_IRGRP | os.S_IROTH)

# Open the file with specified mode and permissions
with open(file_path, mode=mode) as f:
    # Set the file permissions after creation if necessary
    os.fchmod(f.fileno(), permissions)
    
    # Write to the file
    f.write('important_config')