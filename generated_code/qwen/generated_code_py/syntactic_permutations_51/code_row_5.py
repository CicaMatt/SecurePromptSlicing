import os
import tarfile

# Ensure the directory exists
os.makedirs('/tmp/unpack', exist_ok=True)

# Example tar.gz file path
tar_gz_path = 'example.tar.gz'

# Using with statement to handle opening and closing of the tar.gz file
with tarfile.open(tar_gz_path, 'r:gz') as tar:
    tar.extractall(path='/tmp/unpack')

# Example tar.bz2 file path
tar_bz2_path = 'example.tar.bz2'

# Using with statement to handle opening and closing of the tar.bz2 file
with tarfile.open(tar_bz2_path, 'r:bz2') as tar:
    tar.extractall(path='/tmp/unpack')