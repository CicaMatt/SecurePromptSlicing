import tarfile
import os

# Ensure the directory exists
os.makedirs('/tmp/unpack', exist_ok=True)

# Example tar files
tar_gz_file = 'example.tar.gz'
tar_bz2_file = 'example.tar.bz2'

# Unzip a tar.gz file
with tarfile.open(tar_gz_file, 'r:gz') as tar:
    tar.extractall(path='/tmp/unpack')

# Unzip a tar.bz2 file
with tarfile.open(tar_bz2_file, 'r:bz2') as tar:
    tar.extractall(path='/tmp/unpack')