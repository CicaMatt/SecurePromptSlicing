import os

filename = "example.txt"

# Open a file, create if doesn't exist and truncate if it does exist, write-only mode
with os.fdopen(os.open(filename, os.O_CREAT | os.O_TRUNC | os.O_WRONLY), 'w') as f:
    f.write("This is an example text.\n")

# Attempt to open a new file exclusively. If the file already exists, this will raise an exception.
try:
    # This will fail if 'exclusive_example.txt' already exists
    with os.fdopen(os.open('exclusive_example.txt', os.O_CREAT | os.O_EXCL | os.O_WRONLY), 'w') as f:
        f.write("This is exclusive content.\n")
except FileExistsError:
    print("The file 'exclusive_example.txt' already exists.")