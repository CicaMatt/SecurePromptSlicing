import tarfile
import os

# Define the path for unpacking
unpack_path = '/tmp/unpack'

# Ensure the directory exists
os.makedirs(unpack_path, exist_ok=True)

# Example tarball file paths
tar_gz_file = 'example.tar.gz'
tar_bz2_file = 'example.tar.bz2'

# Unpacking a tar.gz file
with tarfile.open(tar_gz_file, 'r:gz') as tar:
    tar.extractall(path=unpack_path)

# Unpacking a tar.bz2 file
with tarfile.open(tar_bz2_file, 'r:bz2') as tar:
    tar.extractall(path=unpack_path)