import os

# Constants for file permission bits
S_IRUSR = 0o400  # Owner has read permission.
S_IWUSR = 0o200  # Owner has write permission.
S_IRGRP = 0o040  # Group has read permission.
S_IROTH = 0o004  # Others have read permission.

# Combine the flags for permissions
permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

try:
    with open('important_config', 'w') as file:
        file.write('important_config')
except OSError as e:
    print(f"Error: {e}")