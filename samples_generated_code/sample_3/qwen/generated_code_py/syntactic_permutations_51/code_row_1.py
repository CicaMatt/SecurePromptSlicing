import tarfile
import os

# Ensure the directory exists
os.makedirs('/tmp/unpack', exist_ok=True)

# Example tar.gz file path
tar_gz_file = 'example.tar.gz'

with tarfile.open(tar_gz_file, mode='r:gz') as tar:
    tar.extractall(path='/tmp/unpack')

# Example tar.bz2 file path
tar_bz2_file = 'example.tar.bz2'

with tarfile.open(tar_bz2_file, mode='r:bz2') as tar:
    tar.extractall(path='/tmp/unpack')