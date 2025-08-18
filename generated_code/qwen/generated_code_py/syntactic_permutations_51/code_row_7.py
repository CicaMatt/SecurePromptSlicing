import tarfile
import os

# Ensure the directory exists
os.makedirs('/tmp/unpack', exist_ok=True)

# Example path to a compressed tar archive
tar_path = 'example.tar.gz'

# Using the with statement to handle the context of opening and closing the tar file
with tarfile.open(tar_path, mode='r:gz') as tar:
    # Extract all contents into /tmp/unpack directory
    tar.extractall(path='/tmp/unpack')