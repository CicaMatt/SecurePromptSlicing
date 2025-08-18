import os
import tarfile

def extract_tar_to_tmp(tar_path):
    tmp_unpack_dir = '/tmp/unpack'
    
    with tarfile.open(tar_path, 'r:*') as tar:
        tar.extractall(path=tmp_unpack_dir)

if __name__ == "__main__":
    # Example usage: replace 'example.tar.gz' with your tar file path
    extract_tar_to_tmp('example.tar.gz')