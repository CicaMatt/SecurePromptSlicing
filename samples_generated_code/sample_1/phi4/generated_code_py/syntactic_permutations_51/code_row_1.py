import os
import tarfile

def extract_tar_to_tmp(tar_path):
    # Ensure the target directory exists
    tmp_unpack_dir = "/tmp/unpack"
    os.makedirs(tmp_unpack_dir, exist_ok=True)

    # Open and extract the tar file using a context manager
    with tarfile.open(tar_path, "r:*") as tar:
        tar.extractall(path=tmp_unpack_dir)

# Example usage (comment out if you don't want to run it immediately)
# Replace 'path_to_your_tar_file.tar.gz' or 'path_to_your_tar_file.tar.bz2'
# with the path to your actual tar file.
# extract_tar_to_tmp('path_to_your_tar_file.tar.gz')