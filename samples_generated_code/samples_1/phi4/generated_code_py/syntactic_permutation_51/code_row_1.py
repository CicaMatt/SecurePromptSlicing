import os
import tarfile

def extract_tar_to_tmp(tar_path):
    tmp_directory = '/tmp/unpack'
    
    # Ensure the target directory exists
    if not os.path.exists(tmp_directory):
        os.makedirs(tmp_directory)
        
    # Open the tar file and extract it to /tmp/unpack
    with tarfile.open(tar_path, 'r:*') as tar:
        tar.extractall(path=tmp_directory)

# Example usage (you should replace 'example.tar.gz' with your actual tar file path)
# extract_tar_to_tmp('example.tar.gz')