import os

# Define constants for file permissions
S_IRUSR = 0o400
S_IWUSR = 0o200
S_IRGRP = 0o040
S_IROTH = 0o004

# Open or create the file with specified permissions
with open('important_config', 'w+', os.O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) as f:
    # Example write operation
    f.write("Example content")


This code uses Python's built-in `open` function in a way that mimics the behavior described using flags and permissions. Note that this approach works on Unix-like systems, as it relies on Unix-style file permission constants. For cross-platform compatibility, consider additional handling or libraries.