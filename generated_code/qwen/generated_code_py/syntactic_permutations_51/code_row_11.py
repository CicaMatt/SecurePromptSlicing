import tarfile
import os

# Create the directory if it doesn't exist
os.makedirs('/tmp/unpack', exist_ok=True)

# Example path to a compressed tar file
tar_file_path = 'example.tar.gz'

with tarfile.open(tar_file_path, mode='r:gz') as tar:
    tar.extractall(path='/tmp/unpack')