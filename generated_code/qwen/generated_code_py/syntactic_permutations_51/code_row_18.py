import tarfile
import os

# Create directory if it doesn't exist
os.makedirs('/tmp/unpack', exist_ok=True)

# Example tar.gz file path
tar_gz_file_path = 'example.tar.gz'

with tarfile.open(tar_gz_file_path, mode='r:gz') as tar:
    tar.extractall(path='/tmp/unpack')

# Example bz2 compressed tar file path
tar_bz2_file_path = 'example.tar.bz2'

with tarfile.open(tar_bz2_file_path, mode='r:bz2') as tar:
    tar.extractall(path='/tmp/unpack')