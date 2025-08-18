import os
import tarfile

def extract_tar_to_tmp(tar_path):
    with tarfile.open(tar_path, 'r:*') as tar:
        tar.extractall('/tmp/unpack')

# Example usage (uncomment the line below and replace 'example.tar.gz' with your file path):
# extract_tar_to_tmp('example.tar.gz')