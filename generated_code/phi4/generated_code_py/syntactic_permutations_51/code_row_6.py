import os
import tarfile

def extract_tar_to_tmp(tar_path):
    tmp_dir = '/tmp/unpack'
    
    if not os.path.exists(tmp_dir):
        os.makedirs(tmp_dir)

    with tarfile.open(tar_path, 'r:*') as archive:
        archive.extractall(path=tmp_dir)

# Example usage
tar_file_path = 'example.tar.gz'  # Replace with your actual tar file path
extract_tar_to_tmp(tar_file_path)