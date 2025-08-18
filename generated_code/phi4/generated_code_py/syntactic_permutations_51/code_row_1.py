import os
import tarfile

def extract_tar_to_tmp(tar_path):
    unpack_dir = '/tmp/unpack'

    # Ensure the directory exists
    if not os.path.exists(unpack_dir):
        os.makedirs(unpack_dir)

    with tarfile.open(tar_path, 'r:*') as tar:
        tar.extractall(path=unpack_dir)
    
# Example usage:
# extract_tar_to_tmp('path_to_your_archive.tar.gz')