import tarfile
import os

# Ensure the directory exists
os.makedirs('/tmp/unpack', exist_ok=True)

# Example usage with gzip compressed tar file
with tarfile.open('example.tar.gz', 'r:gz') as tar:
    tar.extractall(path='/tmp/unpack')

# Example usage with bz2 compressed tar file
with tarfile.open('example.tar.bz2', 'r:bz2') as tar:
    tar.extractall(path='/tmp/unpack')