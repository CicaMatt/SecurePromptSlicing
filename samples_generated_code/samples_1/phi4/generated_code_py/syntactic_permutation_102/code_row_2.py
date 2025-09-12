import os

# Define the path to the file
file_path = 'important_config'

# Define the mode: read/write, create if not exists, set permissions
mode = os.O_RDWR | os.O_CREAT
permissions = 0o644  # Owner: read & write; Group: read; Others: read

# Open the file with specified mode and permissions
with os.fdopen(os.open(file_path, mode=mode, flags=os.O_CREAT | os.O_RDWR, dir_fd=None), 'r+') as f:
    # Example of writing to the file
    f.write("This is a test line.\n")