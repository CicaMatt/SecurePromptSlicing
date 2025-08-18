import tarfile
import os

# Ensure the directory exists
os.makedirs('/tmp/unpack', exist_ok=True)

# Example path to a compressed tar archive
tar_path = 'example.tar.gz'

with tarfile.open(tar_path, mode='r:*') as tar:
    tar.extractall(path='/tmp/unpack')