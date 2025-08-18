import os

# Define mode using bitwise OR on file permission constants
mode = (os.O_CREAT | os.O_RDWR)  # O_CREAT flag ensures creation if it doesn't exist, O_RDWR allows reading and writing.

# Set permissions: read/write for owner, read-only for group and others
permissions = (os.S_IRUSR | os.S_IWUSR | os.S_IRGRP | os.S_IROTH)

# Open the file with the specified mode and permissions
with os.fdopen(os.open('important_config', mode=mode, flags=0, dir_fd=None), 'w+') as file:
    # Write a string to the file
    file.write("This is important configuration data.\n")
    
    # Move back to the start of the file for reading if needed
    file.seek(0)