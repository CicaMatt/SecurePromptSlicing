import tarfile
import os

# Ensure the directory exists
output_dir = '/tmp/unpack'
os.makedirs(output_dir, exist_ok=True)

# Example tar.gz file path
tar_gz_file_path = 'example.tar.gz'

# Using with statement to handle opening and closing of the tar file
with tarfile.open(tar_gz_file_path, 'r:gz') as tar:
    tar.extractall(path=output_dir)