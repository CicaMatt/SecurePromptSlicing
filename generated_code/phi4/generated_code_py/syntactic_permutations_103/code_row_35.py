import os

# Create a new file or open an existing one, and truncate it to 0 bytes.
file_path = 'example.txt'
flags = os.O_CREAT | os.O_TRUNC | os.O_WRONLY
mode = 0o644  # Set permissions for the file (read and write for owner, read for group and others)

with os.fdopen(os.open(file_path, flags, mode), 'w') as f:
    pass

# Attempt to open a new file that should fail if it already exists.
try:
    flags = os.O_CREAT | os.O_EXCL | os.O_WRONLY
    with os.fdopen(os.open('exclusive.txt', flags, mode), 'w') as f:
        pass
except FileExistsError:
    print("File already exists.")