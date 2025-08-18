import tarfile
import os

# Define the path to the tar file and the extraction directory
tar_file_path = 'path_to_your_tarfile.tar'
extraction_dir = '/tmp/unpack'

# Ensure the extraction directory exists
os.makedirs(extraction_dir, exist_ok=True)

# Open the tar file and extract all contents into the specified directory
with tarfile.open(tar_file_path, 'r') as tar:
    tar.extractall(path=extraction_dir)