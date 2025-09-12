import tarfile
import os

# Ensure the destination directory exists
os.makedirs('/tmp/unpack', exist_ok=True)

# Open the archive.zip file as a tarfile and extract all files
with tarfile.open('archive.zip', 'r:zip') as tar:
    tar.extractall(path='/tmp/unpack')