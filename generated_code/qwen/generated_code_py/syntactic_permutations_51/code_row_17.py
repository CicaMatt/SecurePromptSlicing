import tarfile
import os

# Ensure the directory exists
os.makedirs('/tmp/unpack', exist_ok=True)

# Example of using the with statement with tarfile to extract a compressed archive
with tarfile.open('example.tar.gz', 'r:gz') as tar:
    tar.extractall(path='/tmp/unpack')