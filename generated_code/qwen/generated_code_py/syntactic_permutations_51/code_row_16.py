import tarfile
import os

# Ensure the directory exists
os.makedirs('/tmp/unpack', exist_ok=True)

# Example tar.bz2 file path
tar_file_path = 'example.tar.bz2'

# Using with statement to handle the tarfile context
with tarfile.open(tar_file_path, mode='r:bz2') as tar:
    tar.extractall(path='/tmp/unpack')