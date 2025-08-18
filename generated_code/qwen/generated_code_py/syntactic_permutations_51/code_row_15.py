import tarfile
import os

# Ensure the directory exists
os.makedirs('/tmp/unpack', exist_ok=True)

with tarfile.open('example.tar.bz2', 'r:bz2') as tar:
    tar.extractall(path='/tmp/unpack')