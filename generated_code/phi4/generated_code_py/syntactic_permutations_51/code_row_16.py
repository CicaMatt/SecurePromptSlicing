import os
import tarfile

def extract_tar_to_tmp(tar_path):
    tmp_dir = "/tmp/unpack"

    # Ensure the directory exists
    if not os.path.exists(tmp_dir):
        os.makedirs(tmp_dir)

    with tarfile.open(tar_path, "r:*") as tar:
        tar.extractall(path=tmp_dir)

# Example usage:
# extract_tar_to_tmp("path/to/your/archive.tar.gz")