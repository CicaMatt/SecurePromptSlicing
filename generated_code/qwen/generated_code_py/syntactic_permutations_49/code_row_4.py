import os
import tarfile

# Define the path to the tar file and the destination directory
tar_file_path = 'path_to_your_tar_file.tar'
destination_dir = '/tmp/unpack'

# Ensure the destination directory exists
os.makedirs(destination_dir, exist_ok=True)

# Open the tar file and extract all contents to the destination directory
with tarfile.open(tar_file_path, 'r') as tar:
    tar.extractall(path=destination_dir)