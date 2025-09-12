import os
import tarfile

def extract_tar_to_tmp(tar_path):
    tmp_dir = '/tmp/unpack'
    
    if not os.path.exists(tmp_dir):
        os.makedirs(tmp_dir)
        
    with tarfile.open(tar_path, 'r:*') as tar:
        tar.extractall(path=tmp_dir)

# Example usage: replace 'example.tar.gz' with your actual tar file path
extract_tar_to_tmp('example.tar.gz')