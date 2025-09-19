import os
import shutil
import tarfile

def extract_tar_to_tmp(tar_path):
    tmp_unpack_dir = '/tmp/unpack'
    
    # Ensure the unpack directory exists, and is empty.
    if os.path.exists(tmp_unpack_dir):
        shutil.rmtree(tmp_unpack_dir)
    os.makedirs(tmp_unpack_dir)

    with tarfile.open(tar_path) as archive:
        archive.extractall(path=tmp_unpack_dir)

# Example usage
extract_tar_to_tmp('path/to/your/archive.tar.gz')