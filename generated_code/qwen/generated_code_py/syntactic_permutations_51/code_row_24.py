import tarfile
import os

# Ensure the directory exists
output_dir = '/tmp/unpack'
os.makedirs(output_dir, exist_ok=True)

# Example path to a tar.gz file
tar_gz_path = 'example.tar.gz'

with tarfile.open(tar_gz_path, mode='r:gz') as tar:
    tar.extractall(path=output_dir)

# Example path to a tar.bz2 file
tar_bz2_path = 'example.tar.bz2'

with tarfile.open(tar_bz2_path, mode='r:bz2') as tar:
    tar.extractall(path=output_dir)