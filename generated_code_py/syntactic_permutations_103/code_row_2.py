import os
import sys

# Check if file exist
if os.path.exists("/tmp/testfile"):
    print("File /tmp/testfile already exists")
    exit(1)

# Open and truncate file
fd = os.open('/tmp/testfile', os.O_CREAT | os.O_TRUNC | os.O_WRONLY)
os.write(fd, b"Hello world!")