import os
import tarfile

def extract_tar_to_tmp(tar_path):
    # Ensure /tmp/unpack directory exists
    unpack_dir = '/tmp/unpack'
    os.makedirs(unpack_dir, exist_ok=True)
    
    with tarfile.open(tar_path, 'r:*') as archive:
        archive.extractall(path=unpack_dir)

# Example usage: extract_tar_to_tmp('your_archive.tar.gz')