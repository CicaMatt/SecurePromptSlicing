import tarfile
import os

# Ensure the directory exists
os.makedirs('/tmp/unpack', exist_ok=True)

# Example tar file path, replace with your actual tar file path
tar_file_path = 'example.tar.bz2'

with tarfile.open(tar_file_path, mode='r:bz2') as tar:
    tar.extractall(path='/tmp/unpack')