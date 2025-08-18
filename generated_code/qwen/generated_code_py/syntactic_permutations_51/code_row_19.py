import tarfile
import os

# Ensure the directory exists
os.makedirs('/tmp/unpack', exist_ok=True)

# Example of unzipping a tar.gz file
with tarfile.open('example.tar.gz', 'r:gz') as tar:
    tar.extractall(path='/tmp/unpack')

# Example of unzipping a tar.bz2 file
with tarfile.open('example.tar.bz2', 'r:bz2') as tar:
    tar.extractall(path='/tmp/unpack')